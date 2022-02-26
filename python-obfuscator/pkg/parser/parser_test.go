package parser

import (
	"python-obfuscator/pkg/structure"
	"testing"
)

func TestParserFails(t *testing.T) {
	testTableFails(t, map[string]string{
		"tabbed line":                    "\ta='b'\n",
		"double tabbed line in def":      "def f():\n\t\ta='b'\n",
		"double quoted line in constant": "a=\"b\"\n",
		"no doubledot in def":            "def f()\n\treturn 'a'\n",
		"double assignment":              "a=b='a'\n",
		"arguments without coma":         "def f(a b):\n\treturn a\n",
		"strange function call":          "def f(a, b):\n\treturn a\n\nf\n",
		"no empty line at the end":       "a='a'",
	})
}

func TestParserSucceeds(t *testing.T) {
	testTableSuccess(t, map[string]test{
		"simple assignment": {input: "a='a'\n", expected: structure.Program{Content: []structure.ProgramComponent{
			&structure.Assignment{
				Name:     "a",
				Assignee: &structure.Constant{Content: "a"},
			},
		}}},

		"simple function": {input: "def f():\n    return 'a'\n", expected: structure.Program{Content: []structure.ProgramComponent{
			&structure.Function{
				Name:   "f",
				Args:   []string{},
				Body:   []structure.Line{},
				Return: &structure.Constant{Content: "a"},
			},
		}}},

		"function call": {input: "a=input()\nprint(a)\n", expected: structure.Program{Content: []structure.ProgramComponent{
			&structure.Assignment{
				Name: "a",
				Assignee: &structure.FunctionCall{
					Name: "input",
					Args: []structure.Expr{},
				},
			},
			&structure.FunctionCall{
				Name: "print",
				Args: []structure.Expr{
					&structure.Name{Name: "a"},
				},
			},
		}}},

		"chained function calls": {input: "print(int(input()))\n", expected: structure.Program{Content: []structure.ProgramComponent{
			&structure.FunctionCall{
				Name: "print",
				Args: []structure.Expr{
					&structure.FunctionCall{
						Name: "int",
						Args: []structure.Expr{
							&structure.FunctionCall{
								Name: "input",
								Args: []structure.Expr{},
							},
						},
					},
				},
			},
		}}},

		"sample program": {
			input: "def logged():\n\ttmp=input()\n\tprint(tmp)\n\treturn tmp\na=logged()\nb=logged()\nprint(a,b)\n",
			expected: structure.Program{Content: []structure.ProgramComponent{
				&structure.Function{
					Name: "logged",
					Args: []string{},
					Body: []structure.Line{
						&structure.Assignment{
							Name: "tmp",
							Assignee: &structure.FunctionCall{
								Name: "input",
								Args: []structure.Expr{},
							},
						},
						&structure.FunctionCall{
							Name: "print",
							Args: []structure.Expr{
								&structure.Name{Name: "tmp"},
							},
						},
					},
					Return: &structure.Name{Name: "tmp"},
				},
				&structure.Assignment{
					Name: "a",
					Assignee: &structure.FunctionCall{
						Name: "logged",
						Args: []structure.Expr{},
					},
				},
				&structure.Assignment{
					Name: "b",
					Assignee: &structure.FunctionCall{
						Name: "logged",
						Args: []structure.Expr{},
					},
				},
				&structure.FunctionCall{
					Name: "print",
					Args: []structure.Expr{
						&structure.Name{Name: "a"},
						&structure.Name{Name: "b"},
					},
				},
			}}},
	})
}
