package parser

import "python-obfuscator/pkg/structure"

//go:generate goyacc -l -o parser.go parser.y
func Parse(input string) (structure.Program, error) {
	lex := NewLexer(input)
	_ = yyParse(lex)

	return lex.result, lex.err
}

func EnableDebug() {
	yyDebug = 4
	yyErrorVerbose = true
}
