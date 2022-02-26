package parser

import (
	"fmt"
	"os"
	"parser-generator/pkg/generators"
	"parser-generator/pkg/structure"
	"path/filepath"
	"strconv"
	"strings"
)

func GenerateParser(grammar structure.Grammar, path string) error {
	gen := &generator{
		grammar: grammar,
		path:    path,
	}

	return gen.generate()
}

type generator struct {
	grammar structure.Grammar
	path    string
}

func (r *generator) generate() error {
	if err := os.MkdirAll(r.path, os.ModePerm); err != nil {
		return fmt.Errorf("unable to create directory for parser: %w", err)
	}

	treeFile := filepath.Join(r.path, strings.ToLower(r.grammar.Name)+"_tree.go")

	if err := generators.GenerateCode("tree", treeFile, map[string]interface{}{}); err != nil {
		return fmt.Errorf("unable to generate tree: %w", err)
	}

	parserFile := filepath.Join(r.path, strings.ToLower(r.grammar.Name)+"_parser.go")

	if err := generators.GenerateCode("parser", parserFile, r.parserValues()); err != nil {
		return fmt.Errorf("unable to generate parser: %w", err)
	}

	return nil
}

func (r *generator) parserValues() map[string]interface{} {
	vars := map[string]interface{}{
		"Name":    r.grammar.Name,
		"Start":   r.grammar.Start,
		"Parsers": r.generateParsers(),
		"Types":   r.generateTypes(),
	}

	return vars
}

type Type struct {
	Name   string
	Params []structure.Param
}

func (r *generator) generateTypes() []Type {
	var res []Type

	for _, nonTerm := range r.grammar.NonTerminals {
		res = append(res, Type{
			Name:   nonTerm.Name,
			Params: nonTerm.Returns,
		})
	}

	return res
}

type ParsingCase struct {
	Kinds []string
	Text  string
}

type Parser struct {
	Name   string
	Params []structure.Param
	Cases  []ParsingCase
}

func (r *generator) generateParsers() []Parser {
	var res []Parser

	for _, nonTerm := range r.grammar.NonTerminals {
		res = append(res, r.generateParser(nonTerm))
	}

	return res
}

func (r *generator) generateParser(nonTerm structure.NonTerminal) Parser {
	res := Parser{
		Name:   nonTerm.Name,
		Params: nil,
		Cases:  nil,
	}

	for _, param := range nonTerm.Params {
		res.Params = append(res.Params, param)
	}

	for _, rule := range nonTerm.Rules {
		res.Cases = append(res.Cases, r.generateRule(nonTerm, rule))
	}

	return res
}

func (r *generator) generateRule(nonTerm structure.NonTerminal, rule structure.Rule) ParsingCase {
	res := ParsingCase{
		Kinds: nil,
		Text:  "",
	}

	bld := strings.Builder{}

	for cs := range r.grammar.First(nonTerm, rule, 0) {
		res.Kinds = append(res.Kinds, cs.Name)
	}

	for ind, el := range rule.Elements {
		if termRule, ok := r.grammar.Terminals[el.Name]; ok {
			bld.WriteString("res.SetChildren(append(res.GetChildren(), &BaseTree{Node: \"" + termRule.Name + ":\" + token.value}))\n")

			if len(el.Code) > 0 {
				bld.WriteString(el.Code)
			}

			if !termRule.IsEps() {
				bld.WriteString("_, err" + strconv.Itoa(ind) + " := r.lexer.NextToken()\n")
				bld.WriteString("if err" + strconv.Itoa(ind) + "!= nil {\n")
				bld.WriteString("\treturn " + nonTerm.Name + "Tree{}, fmt.Errorf(\"unable to get token from lexer: %w\", err" + strconv.Itoa(ind) + ")\n")
				bld.WriteString("}\n")
			}
		} else if _, ok := r.grammar.NonTerminals[el.Name]; ok {
			bld.WriteString("res" + strconv.Itoa(ind) + ", err := r." + el.Name + "(" + el.Params + ")\n")
			bld.WriteString("if err != nil {\n")
			bld.WriteString("\treturn " + nonTerm.Name + "Tree{}, fmt.Errorf(\"unable to parse " + el.Name + " in " + nonTerm.Name + ": %w\", err)\n")
			bld.WriteString("}\n")
			bld.WriteString("res.SetChildren(append(res.GetChildren(), &res" + strconv.Itoa(ind) + "))\n")

			if len(el.Code) > 0 {
				bld.WriteString(el.Code)
			}
		} else {
			panic("I hate to panic, but " + el.Name + " is neither terminal nor non-terminal")
		}

	}

	res.Text = bld.String()

	return res
}
