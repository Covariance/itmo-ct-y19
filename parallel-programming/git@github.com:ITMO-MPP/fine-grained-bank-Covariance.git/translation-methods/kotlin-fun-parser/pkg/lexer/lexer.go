package lexer

import (
	"fmt"
	"unicode"
)

type TokenType int

const (
	EPS TokenType = iota
	FUN
	NAME
	COMA
	DOUBLEDOT
	LBRACKET
	RBRACKET
	EQUALS
	LGENBRACKET
	RGENBRACKET
)

type Token struct {
	tp      TokenType
	content []rune
}

func (r *Token) Type() TokenType {
	return r.tp
}

func (r *Token) Contents() string {
	return string(r.content)
}

func (r Token) String() string {
	switch r.tp {
	case EPS:
		return "EPS"
	case FUN:
		return "FUN"
	case NAME:
		return "NAME " + r.Contents()
	case COMA:
		return "COMA"
	case DOUBLEDOT:
		return "DOUBLEDOT"
	case LBRACKET:
		return "LBRACKET"
	case RBRACKET:
		return "RBRACKET"
	case EQUALS:
		return "EQUALS"
	case LGENBRACKET:
		return "LGENBRACKET"
	case RGENBRACKET:
		return "RGENBRACKET"
	}

	return "UNDEFINED"
}

type Lexer interface {
	CurrentToken() Token
	NextToken() (Token, error)
}

type RuneSliceLexer struct {
	current Token
	input   []rune
	pos     int
}

func NewLexer(input []rune) Lexer {
	return &RuneSliceLexer{
		input: input,
		pos:   0,
	}
}

func (r *RuneSliceLexer) skipSpaces() {
	for r.pos != len(r.input) && unicode.IsSpace(r.input[r.pos]) {
		r.pos++
	}
}

func (r *RuneSliceLexer) nextRune() rune {
	if r.pos == len(r.input) {
		return -1
	}
	r.pos++
	return r.input[r.pos-1]
}

func (r *RuneSliceLexer) CurrentToken() Token {
	return r.current
}

func (r *RuneSliceLexer) nextToken() (Token, error) { //nolint:gocyclo
	r.skipSpaces()
	if r.pos == len(r.input) {
		return Token{EPS, nil}, nil
	}

	rn := r.nextRune()

	if rn == ',' {
		return Token{COMA, nil}, nil
	}
	if rn == ':' {
		return Token{DOUBLEDOT, nil}, nil
	}
	if rn == '(' {
		return Token{LBRACKET, nil}, nil
	}
	if rn == ')' {
		return Token{RBRACKET, nil}, nil
	}
	if rn == '=' {
		return Token{EQUALS, nil}, nil
	}
	if rn == '<' {
		return Token{LGENBRACKET, nil}, nil
	}
	if rn == '>' {
		return Token{RGENBRACKET, nil}, nil
	}

	if !unicode.IsLetter(rn) {
		return Token{}, fmt.Errorf("unable to recognize token %c at position %d", rn, r.pos-1)
	}

	word := []rune{rn}

	for r.pos != len(r.input) && (unicode.IsLetter(r.input[r.pos]) || unicode.IsDigit(r.input[r.pos])) {
		word = append(word, r.input[r.pos])
		r.pos++
	}

	if string(word) == "fun" {
		if r.pos != len(r.input) && unicode.IsSpace(r.input[r.pos]) {
			r.pos++
			return Token{FUN, nil}, nil
		}
		return Token{}, fmt.Errorf("no whitespace after 'fun' keyword, instead found: %c", r.input[r.pos])
	}

	return Token{NAME, word}, nil
}

func (r *RuneSliceLexer) NextToken() (Token, error) {
	token, err := r.nextToken()
	r.current = token
	return token, err
}
