package lexer

import (
	"fmt"
	"os"
	"parser-generator/pkg/generators"
	"parser-generator/pkg/structure"
	"path/filepath"
	"strings"
)

func GenerateLexer(grammar structure.Grammar, path string) error {
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
		return fmt.Errorf("unable to create directory for lexer: %w", err)
	}

	lexerFile := filepath.Join(r.path, strings.ToLower(r.grammar.Name)+"_lexer.go")

	if err := generators.GenerateCode("lexer", lexerFile, r.lexerValues()); err != nil {
		return fmt.Errorf("unable to generate lexer: %w", err)
	}

	return nil
}

func (r *generator) lexerValues() map[string]interface{} {
	var tokens []struct {
		Kind  string
		Regex string
	}

	for _, terminal := range r.grammar.Terminals {
		tokens = append(tokens, struct {
			Kind  string
			Regex string
		}{Kind: terminal.Name, Regex: terminal.Regex})
	}

	return map[string]interface{}{
		"Tokens": tokens,
		"Name":   r.grammar.Name,
	}
}
