package parser

import (
	"fmt"
	"mt-2/pkg/graph"
	"mt-2/pkg/lexer"
)

func Parse(input []rune) (*graph.Tree, error) {
	lex := lexer.NewLexer(input)

	_, err := lex.NextToken()
	if err != nil {
		return nil, err
	}

	return ParseFun(lex)
}

type Parser func(lexer.Lexer) (*graph.Tree, error)

func mismatchError(where string, expected string, got lexer.Token) error {
	return fmt.Errorf("token type mismatch in %s: expected %s, got %s", where, expected, got)
}

func nextTokenError(where string, nested error) error {
	return fmt.Errorf("unable to take next token in %s: %w", where, nested)
}

func nestedError(where string, inner string, nested error) error {
	return fmt.Errorf("unable to parse %s in %s: %w", inner, where, nested)
}

func ParseGen(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Gen",
		Children: nil,
	}

	token := lex.CurrentToken()

	switch token.Type() {
	case lexer.LGENBRACKET:
		_, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("Gen", err)
		}

		tp, err := ParseType(lex)
		if err != nil {
			return nil, nestedError("Gen", "Type", err)
		}

		tok := lex.CurrentToken()
		if tok.Type() != lexer.RGENBRACKET {
			return nil, mismatchError("Gen", "RGENBRACKET", tok)
		}

		_, err = lex.NextToken()
		if err != nil {
			return nil, nextTokenError("Gen", err)
		}

		tree.Children = []*graph.Tree{
			{Node: "<", Children: nil},
			tp,
			{Node: ">", Children: nil},
		}
	default:
		tree.Children = []*graph.Tree{
			{Node: "eps", Children: nil},
		}
	}

	return &tree, nil
}

func ParseType(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Type",
		Children: nil,
	}

	token := lex.CurrentToken()
	if token.Type() != lexer.NAME {
		return nil, mismatchError("Type", "NAME", token)
	}

	_, err := lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Type", err)
	}

	gen, err := ParseGen(lex)
	if err != nil {
		return nil, nestedError("Type", "Gen", err)
	}

	tree.Children = []*graph.Tree{
		{Node: "type: " + token.Contents(), Children: nil},
		gen,
	}

	return &tree, nil
}

func ParseFType(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "FType",
		Children: nil,
	}

	token := lex.CurrentToken()
	switch token.Type() {
	case lexer.DOUBLEDOT:
		_, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("FType", err)
		}

		tp, err := ParseType(lex)
		if err != nil {
			return nil, nestedError("FType", "Type", err)
		}

		tree.Children = []*graph.Tree{
			{Node: ":", Children: nil},
			tp,
		}
	default:
		tree.Children = []*graph.Tree{
			{Node: "eps", Children: nil},
		}
	}

	return &tree, nil
}

func ParseArg(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Arg",
		Children: nil,
	}

	name := lex.CurrentToken()
	if name.Type() != lexer.NAME {
		return nil, mismatchError("Arg", "NAME", name)
	}

	doubledot, err := lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Arg", err)
	}
	if doubledot.Type() != lexer.DOUBLEDOT {
		return nil, mismatchError("Arg", "DOUBLEDOT", doubledot)
	}

	_, err = lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Arg", err)
	}

	tp, err := ParseType(lex)
	if err != nil {
		return nil, nestedError("Arg", "Type", err)
	}

	tree.Children = []*graph.Tree{
		{Node: "name: " + name.Contents(), Children: nil},
		{Node: ":", Children: nil},
		tp,
	}

	return &tree, nil
}

func ParseDefArg(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "DefArg",
		Children: nil,
	}

	token := lex.CurrentToken()

	switch token.Type() {
	case lexer.COMA:
		_, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("DefArg", err)
		}

		arg, err := ParseArg(lex)
		if err != nil {
			return nil, nestedError("DefArg", "Arg", err)
		}

		eq := lex.CurrentToken()
		if eq.Type() != lexer.EQUALS {
			return nil, mismatchError("DefArg", "EQUALS", eq)
		}

		val, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("DefArg", err)
		}
		if val.Type() != lexer.NAME {
			return nil, mismatchError("DefArg", "NAME", val)
		}

		_, err = lex.NextToken()
		if err != nil {
			return nil, nextTokenError("DefArg", err)
		}

		nested, err := ParseDefArg(lex)
		if err != nil {
			return nil, nestedError("DefArg", "DefArg", err)
		}

		tree.Children = []*graph.Tree{
			{Node: ",", Children: nil},
			arg,
			{Node: "=", Children: nil},
			{Node: "value: " + val.Contents(), Children: nil},
			nested,
		}

	default:
		tree.Children = []*graph.Tree{
			{Node: "eps", Children: nil},
		}
	}

	return &tree, nil
}

func ParseTail(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Tail",
		Children: nil,
	}

	token := lex.CurrentToken()

	switch token.Type() {
	case lexer.EQUALS:
		val, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("Tail", err)
		}
		if val.Type() != lexer.NAME {
			return nil, mismatchError("Tail", "NAME", val)
		}

		_, err = lex.NextToken()
		if err != nil {
			return nil, nextTokenError("Tail", err)
		}

		defArg, err := ParseDefArg(lex)
		if err != nil {
			return nil, nestedError("Tail", "DefArg", err)
		}

		tree.Children = []*graph.Tree{
			{Node: "=", Children: nil},
			{Node: "value: " + val.Contents(), Children: nil},
			defArg,
		}

	case lexer.COMA:
		_, err := lex.NextToken()
		if err != nil {
			return nil, nextTokenError("Tail", err)
		}

		arg, err := ParseArg(lex)
		if err != nil {
			return nil, nestedError("Tail", "Arg", err)
		}

		tail, err := ParseTail(lex)
		if err != nil {
			return nil, nestedError("Tail", "Tail", err)
		}

		tree.Children = []*graph.Tree{
			{Node: ",", Children: nil},
			arg,
			tail,
		}

	default:
		tree.Children = []*graph.Tree{
			{Node: "eps", Children: nil},
		}
	}

	return &tree, nil
}

func ParseArgs(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Args",
		Children: nil,
	}

	token := lex.CurrentToken()

	switch token.Type() {
	case lexer.NAME:
		arg, err := ParseArg(lex)
		if err != nil {
			return nil, nestedError("Args", "Arg", err)
		}

		tail, err := ParseTail(lex)
		if err != nil {
			return nil, nestedError("Args", "Tail", err)
		}

		tree.Children = []*graph.Tree{
			arg,
			tail,
		}

	default:
		tree.Children = []*graph.Tree{
			{Node: "eps", Children: nil},
		}
	}

	return &tree, nil
}

func ParseFun(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Fun",
		Children: nil,
	}

	fun := lex.CurrentToken()
	if fun.Type() != lexer.FUN {
		return nil, mismatchError("Fun", "FUN", fun)
	}

	name, err := lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Fun", err)
	}
	if name.Type() != lexer.NAME {
		return nil, mismatchError("Fun", "NAME", name)
	}

	lbr, err := lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Fun", err)
	}
	if lbr.Type() != lexer.LBRACKET {
		return nil, mismatchError("Fun", "LBRACKET", lbr)
	}

	_, err = lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Fun", err)
	}

	args, err := ParseArgs(lex)
	if err != nil {
		return nil, nestedError("Fun", "Args", err)
	}

	rbr := lex.CurrentToken()
	if rbr.Type() != lexer.RBRACKET {
		return nil, mismatchError("Fun", "RBRACKET", rbr)
	}

	_, err = lex.NextToken()
	if err != nil {
		return nil, nextTokenError("Fun", err)
	}

	ftp, err := ParseFType(lex)
	if err != nil {
		return nil, nestedError("Fun", "FType", err)
	}

	eps := lex.CurrentToken()
	if eps.Type() != lexer.EPS {
		return nil, mismatchError("Fun", "EPS", eps)
	}

	tree.Children = []*graph.Tree{
		{Node: "fun", Children: nil},
		{Node: "name: " + name.Contents(), Children: nil},
		{Node: "(", Children: nil},
		args,
		{Node: ")", Children: nil},
		ftp,
		{Node: "eps", Children: nil},
	}

	return &tree, nil
}
