package parser

import (
	"errors"
	"python-obfuscator/pkg/structure"
	"reflect"
	"unicode"
)

type lexer struct {
	input []rune
	pos   int

	result structure.Program
	err    error
}

func reverse(s interface{}) {
	n := reflect.ValueOf(s).Len()
	swap := reflect.Swapper(s)
	for i, j := 0, n-1; i < j; i, j = i+1, j-1 {
		swap(i, j)
	}
}

func NewLexer(input string) *lexer {
	return &lexer{
		input: []rune(input),
		pos:   0,
	}
}

func (r *lexer) nextRune() rune {
	if r.pos >= len(r.input) {
		return 0
	}
	r.pos++
	return r.input[r.pos-1]
}

func (r *lexer) Lex(val *yySymType) int {
	if r.pos >= len(r.input) {
		return 0
	}

	rn := r.nextRune()

	if rn == '\n' {
		for r.pos < len(r.input) && rn == '\n' {
			rn = r.nextRune()
		}
		if r.pos < len(r.input) {
			r.pos--
		}
		return BREAK
	}

	if rn == '\t' {
		return TAB
	}

	if rn == ' ' {
		r.pos += 3
		return TAB
	}

	if rn == ',' || rn == '(' || rn == ')' || rn == ':' || rn == '\'' || rn == '=' {
		return int(rn)
	}

	word := []rune{rn}

	for r.pos != len(r.input) && (unicode.IsLetter(r.input[r.pos]) || unicode.IsDigit(r.input[r.pos])) {
		word = append(word, r.input[r.pos])
		r.pos++
	}

	if string(word) == "def" {
		// Need to eat that space
		_ = r.nextRune()
		return DEF
	}

	if string(word) == "return" {
		// Need to eat that space
		_ = r.nextRune()
		return RETURN
	}

	val.str = string(word)
	return NAME
}

func (r *lexer) Error(s string) {
	r.err = errors.New(s)
}
