package parser

import (
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"mt-2/pkg/graph"
	"mt-2/pkg/lexer"
	"testing"
)

func (r Parser) testParserResult(t *testing.T, input string, expected graph.Tree) {
	t.Helper()

	lex := lexer.NewLexer([]rune(input))
	_, err := lex.NextToken()
	require.NoError(t, err)

	res, err := r(lex)
	require.NoError(t, err)

	assert.True(t, res.Equals(&expected), "Tree does not match: "+res.String())
}

func (r Parser) testParserFails(t *testing.T, input string) {
	t.Helper()

	lex := lexer.NewLexer([]rune(input))
	_, err := lex.NextToken()
	require.NoError(t, err)

	_, err = r(lex)

	assert.Error(t, err, "Tree was parsed")
}

func (r Parser) testTableFails(t *testing.T, table map[string]string) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			r.testParserFails(t, test)
		})
	}
}

type test struct {
	input    string
	expected graph.Tree
}

func (r Parser) testTableSuccess(t *testing.T, table map[string]test) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			r.testParserResult(t, test.input, test.expected)
		})
	}
}
