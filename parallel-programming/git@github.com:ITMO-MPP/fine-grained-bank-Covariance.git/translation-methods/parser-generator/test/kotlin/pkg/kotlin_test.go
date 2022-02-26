package parser

import (
	"fmt"
	"testing"
)

func TestSomething(t *testing.T) {
	expr := "fun name(what: type)"

	lex := NewLexer(expr)

	prs := kotlinParser{lexer: lex}

	tree, err := (&prs).Parse()
	if err != nil {
		t.Fatal(err)
	}
	fmt.Println(tree.String())
}
