package parser

import (
	"fmt"
	"github.com/antlr/antlr4/runtime/Go/antlr"
	"parser-generator/pkg/structure"
)

func ParseGospodGrammar(inputFile string) (*structure.Grammar, error) {
	fileStream, err := antlr.NewFileStream(inputFile)
	if err != nil {
		return nil, fmt.Errorf("unable to read input parser: %w", err)
	}

	lexer := NewGospodGrammarLexer(fileStream)
	stream := antlr.NewCommonTokenStream(lexer, 0)

	parser := NewGospodGrammarParser(stream)

	res := &structure.Grammar{
		Terminals:    map[string]structure.Terminal{},
		NonTerminals: map[string]structure.NonTerminal{},
	}
	parser.Gram(res)

	return res, nil
}
