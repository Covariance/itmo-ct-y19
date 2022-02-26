package parser

import "fmt"

type wtfParser struct {
	lexer wtfLexer
}

func (r *wtfParser) Parse(input string) (*Tree, error) {
	_, err := r.lexer.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to get token from lexer: %w", err)
	}

	res, err := r.kind()
	if err != nil {
		return nil, fmt.Errorf("unable to parse input: %w", err)
	}

	if r.lexer.Current().kind != END {
		return nil, fmt.Errorf("expecting end of input, got: %s", r.lexer.Current().kind.String())
	}

	return res, nil
}

func (r *wtfParser) kind(
    
) (*Tree, error) {
    res := Tree{Node: "kind"}

    token := r.lexer.Current()

    switch token {
        
        default:
            return nil, fmt.Errorf("expected one of []", token.kind.String())
    }

    return &res, nil
}

