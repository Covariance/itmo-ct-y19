package parser

import (
	"fmt"
	"mt-2/pkg/graph"
	"mt-2/pkg/lexer"
)

func Parse(input []rune) (*graph.Tree, error) {
	lex := lexer.NewLexer(input)

	return parseFun(lex)
}

type Parser func(lexer.Lexer) (*graph.Tree, error)

func parseFun(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Fun",
		Children: nil,
	}

	fun, err := lex.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to parse \"fun\" in Fun: %w", err)
	}
	if fun.Type() != lexer.FUN {
		return nil, fmt.Errorf("expected FUN, got %s", fun)
	}

	name, err := lex.NextToken()
	if err != nil {
		return &tree, fmt.Errorf("unable to parse name in Fun: %w", err)
	}
	if name.Type() != lexer.NAME {
		return nil, fmt.Errorf("expected NAME, got %s", name)
	}

	lbr, err := lex.NextToken()
	if err != nil {
		return &tree, fmt.Errorf("unable to parse left bracket in Fun: %w", err)
	}
	if lbr.Type() != lexer.LBRACKET {
		return nil, fmt.Errorf("expected LBRACKET, got %s", lbr)
	}

	argTree, err := parseArgs(lex)
	if err != nil {
		return &tree, fmt.Errorf("unable to parse Args in Fun: %w", err)
	}

	rbr := lex.CurrentToken()
	if rbr.Type() != lexer.RBRACKET {
		return nil, fmt.Errorf("expected RBRACKET, got %s", rbr)
	}

	ftypeTree, err := parseFType(lex)
	if err != nil {
		return &tree, fmt.Errorf("unable to parse FType in Fun: %w", err)
	}

	eps := lex.CurrentToken()
	if eps.Type() != lexer.EPS {
		return nil, fmt.Errorf("expected EPS, got %s", eps)
	}

	tree.Children = []*graph.Tree{
		{Node: "fun", Children: nil},
		{Node: fmt.Sprintf("name: %s", name.Contents()), Children: nil},
		{Node: "(", Children: nil},
		argTree,
		{Node: ")", Children: nil},
		ftypeTree,
		{Node: "eps", Children: nil},
	}

	return &tree, nil
}

func parseFType(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "FType",
		Children: nil,
	}

	next, err := lex.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to parse FType: %w", err)
	}

	switch next.Type() { //nolint:exhaustive
	case lexer.EPS:
		return &tree, nil

	case lexer.DOUBLEDOT:
		tp, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse NAME in FType: %w", err)
		}
		if tp.Type() != lexer.NAME {
			return nil, fmt.Errorf("expected NAME, got %s", tp)
		}
		tree.Children = []*graph.Tree{
			{Node: ":", Children: nil},
			{Node: fmt.Sprintf("type: %s", tp.Contents()), Children: nil},
		}

		if token := lex.CurrentToken(); token.Type() != lexer.EPS {
			if _, err := lex.NextToken(); err != nil {
				return nil, fmt.Errorf("cannot parse follow in FType: %w", err)
			}
		}

		return &tree, nil

	default:
		return nil, fmt.Errorf("expected EPS or DOUBLEDOT, got %s", next)
	}
}

func parseArgs(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "Args",
		Children: nil,
	}

	next, err := lex.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to parse Args: %w", err)
	}

	switch next.Type() { //nolint:exhaustive
	case lexer.RBRACKET:
		return &tree, nil

	case lexer.NAME:
		dbldot, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse DOUBLEDOT in Args: %w", err)
		}
		if dbldot.Type() != lexer.DOUBLEDOT {
			return nil, fmt.Errorf("expected DOUBLEDOT, got %s", dbldot)
		}

		tp, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse NAME in Args: %w", err)
		}
		if tp.Type() != lexer.NAME {
			return nil, fmt.Errorf("expected NAME, got %s", tp)
		}

		argTail, err := parseArgTail(lex)
		if err != nil {
			return nil, fmt.Errorf("unable to parse ArgTail in Args: %w", err)
		}

		tree.Children = []*graph.Tree{
			{Node: fmt.Sprintf("name: %s", next.Contents()), Children: nil},
			{Node: ":", Children: nil},
			{Node: fmt.Sprintf("type: %s", tp.Contents()), Children: nil},
			argTail,
		}

		if token := lex.CurrentToken(); token.Type() != lexer.RBRACKET {
			if _, err := lex.NextToken(); err != nil {
				return nil, fmt.Errorf("cannot parse follow in Args: %w", err)
			}
		}

		return &tree, nil

	default:
		return nil, fmt.Errorf("expected RBRACKET or NAME, got %s", next)
	}
}

func parseArgTail(lex lexer.Lexer) (*graph.Tree, error) {
	tree := graph.Tree{
		Node:     "ArgTail",
		Children: nil,
	}

	next, err := lex.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to parse ArgTail: %w", err)
	}

	switch next.Type() { //nolint:exhaustive
	case lexer.RBRACKET:
		return &tree, nil

	case lexer.COMA:
		name, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse NAME in ArgTail: %w", err)
		}
		if name.Type() != lexer.NAME {
			return nil, fmt.Errorf("expected NAME, got %s", name)
		}

		dbldot, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse DOUBLEDOT in ArgTail: %w", err)
		}
		if dbldot.Type() != lexer.DOUBLEDOT {
			return nil, fmt.Errorf("expected DOUBLEDOT, got %s", dbldot)
		}

		tp, err := lex.NextToken()
		if err != nil {
			return nil, fmt.Errorf("unable to parse NAME in ArgTail: %w", err)
		}
		if tp.Type() != lexer.NAME {
			return nil, fmt.Errorf("expected NAME, got %s", tp)
		}

		argTail, err := parseArgTail(lex)
		if err != nil {
			return nil, fmt.Errorf("unable to parse ArgTail in ArgTail: %w", err)
		}

		tree.Children = []*graph.Tree{
			{Node: ",", Children: nil},
			{Node: fmt.Sprintf("name: %s", name.Contents()), Children: nil},
			{Node: ":", Children: nil},
			{Node: fmt.Sprintf("type: %s", tp.Contents()), Children: nil},
			argTail,
		}

		if token := lex.CurrentToken(); token.Type() != lexer.RBRACKET {
			if _, err := lex.NextToken(); err != nil {
				return nil, fmt.Errorf("cannot parse follow in ArgTail: %w", err)
			}
		}

		return &tree, nil

	default:
		return nil, fmt.Errorf("expected RBRACKET or COMA, got %s", next)
	}
}
