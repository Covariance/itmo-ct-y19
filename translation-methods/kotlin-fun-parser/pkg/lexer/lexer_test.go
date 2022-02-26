package lexer

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

type test struct {
	expected []Token
	input    string
}

func assertByLexer(t *testing.T, expected []Token, lexer Lexer) {
	t.Helper()

	var tokens []Token
	for range expected {
		token, err := lexer.NextToken()
		require.NoError(t, err)
		tokens = append(tokens, token)
	}

	// Assert
	for i, exp := range expected {
		assert.Equal(t, exp.tp, tokens[i].tp)
		assert.Equal(t, exp.content, tokens[i].content)
	}
}

func (r *test) assertTokens(t *testing.T) {
	t.Helper()

	lexer := NewLexer([]rune(r.input))

	assertByLexer(t, r.expected, lexer)
}

func (r *test) assertTokensThenError(t *testing.T) {
	t.Helper()

	lexer := NewLexer([]rune(r.input))

	assertByLexer(t, r.expected, lexer)

	_, err := lexer.NextToken()

	assert.Error(t, err)
}

func runTableTestSuccess(t *testing.T, table map[string]test) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			test.assertTokens(t)
		})
	}
}

func runTableTestFailure(t *testing.T, table map[string]test) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			test.assertTokensThenError(t)
		})
	}
}

func TestEPS(t *testing.T) {
	runTableTestSuccess(t, map[string]test{
		"empty input":            {[]Token{{EPS, nil}}, ""},
		"input with spaces":      {[]Token{{EPS, nil}}, "         "},
		"input with space runes": {[]Token{{EPS, nil}}, " \t\n \t \n  "},
	})
}

func TestName(t *testing.T) {
	runTableTestSuccess(t, map[string]test{
		"valid name":                         {[]Token{{NAME, []rune("ValidName")}}, "   ValidName"},
		"valid name with digits":             {[]Token{{NAME, []rune("An0therVal1d")}}, "   An0therVal1d"},
		"valid name with unicode characters": {[]Token{{NAME, []rune("ВалиднаяФункция1")}}, "ВалиднаяФункция1"},
	})

	runTableTestFailure(t, map[string]test{
		"invalid name starting with digit": {nil, "1nval1d name"},
	})
}

func TestFun(t *testing.T) {
	runTableTestSuccess(t, map[string]test{
		"valid fun": {[]Token{{FUN, nil}}, "fun smth()"},
	})

	runTableTestFailure(t, map[string]test{
		"fun without whitespace": {nil, "fun()"},
	})
}

func TestStandaloneSymbols(t *testing.T) {
	runTableTestSuccess(t, map[string]test{
		"coma":                  {[]Token{{COMA, nil}}, "\t ,"},
		"doubledot":             {[]Token{{DOUBLEDOT, nil}}, "\t :"},
		"left bracket":          {[]Token{{LBRACKET, nil}}, "\t ("},
		"right bracket":         {[]Token{{RBRACKET, nil}}, "\t )"},
		"equals":                {[]Token{{EQUALS, nil}}, "\t ="},
		"left generic bracket":  {[]Token{{LGENBRACKET, nil}}, "\t <"},
		"right generic bracket": {[]Token{{RGENBRACKET, nil}}, "\t >"},
	})
}

func TestMultiple(t *testing.T) {
	runTableTestSuccess(t, map[string]test{
		"valid function signature": {[]Token{
			{FUN, nil},
			{NAME, []rune("smth")},
			{LBRACKET, nil},
			{NAME, []rune("smth")},
			{DOUBLEDOT, nil},
			{NAME, []rune("smth")},
			{COMA, nil},
			{NAME, []rune("smth")},
			{DOUBLEDOT, nil},
			{NAME, []rune("smth")},
			{RBRACKET, nil},
			{DOUBLEDOT, nil},
			{NAME, []rune("smth")},
			{EPS, nil},
		}, "fun smth(smth : smth, smth : smth) : smth"},
		"multiple names correct separation": {[]Token{
			{NAME, []rune("name1")},
			{NAME, []rune("name2")},
			{COMA, nil},
			{NAME, []rune("name3")},
			{LBRACKET, nil},
			{RBRACKET, nil},
			{NAME, []rune("name4")},
			{DOUBLEDOT, nil},
			{NAME, []rune("name5")},
			{EPS, nil},
		}, "  name1\t \tname2,name3()name4:name5"},
		"interesting signatures": {[]Token{
			{FUN, nil},
			{NAME, []rune("what")},
			{NAME, []rune("type")},
			{LGENBRACKET, nil},
			{NAME, []rune("Int")},
			{RGENBRACKET, nil},
			{EQUALS, nil},
			{NAME, []rune("other")},
			{LGENBRACKET, nil},
			{NAME, []rune("List")},
			{LGENBRACKET, nil},
			{NAME, []rune("Bool")},
			{RGENBRACKET, nil},
			{RGENBRACKET, nil},
		}, "  fun what type<Int> = other<List<Bool>>"},
	})
}
