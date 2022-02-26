package parser

import (
	"fmt"
	"testing"
)

func TestSomething(t *testing.T) {
	expr := "2 ** 3 * 3 ** 2"

	lex := NewLexer(expr)

	prs := calculatorParser{lexer: lex}

	tree, err := (&prs).Parse()
	if err != nil {
		t.Fatal(err)
	}
	res := tree.(*eTree)
	fmt.Println(res.x)
}
