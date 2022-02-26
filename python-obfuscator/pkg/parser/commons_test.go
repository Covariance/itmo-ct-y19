package parser

import (
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	deep "gotest.tools/assert"
	"python-obfuscator/pkg/structure"
	"testing"
)

func testParserResult(t *testing.T, input string, expected structure.Program) {
	t.Helper()

	res, err := Parse(input)
	require.NoError(t, err)

	deep.DeepEqual(t, res, expected)
}

func testParserFails(t *testing.T, input string) {
	t.Helper()

	_, err := Parse(input)

	assert.Error(t, err, "Program was parsed")
}

type test struct {
	input    string
	expected structure.Program
}

func testTableFails(t *testing.T, table map[string]string) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			testParserFails(t, test)
		})
	}
}

func testTableSuccess(t *testing.T, table map[string]test) {
	t.Helper()

	for name, test := range table {
		t.Run(name, func(t *testing.T) {
			testParserResult(t, test.input, test.expected)
		})
	}
}
