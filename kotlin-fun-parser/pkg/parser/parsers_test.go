package parser

import (
	"mt-2/pkg/graph"
	"testing"
)

func TestNoParseGen(t *testing.T) {
	Parser(ParseGen).testTableFails(t, map[string]string{
		"matching yet empty brackets": "<>",
		"non-matching brackets":       "<Type",
		"more non-matching brackets":  "<Type<>",
	})
}

func TestParseGen(t *testing.T) {
	Parser(ParseGen).testTableSuccess(t, map[string]test{
		"epsilon": {input: "", expected: graph.Tree{
			Node:     "Gen",
			Children: []*graph.Tree{{Node: "eps", Children: nil}},
		}},
		"simple generic type": {input: "<Int>", expected: graph.Tree{
			Node: "Gen",
			Children: []*graph.Tree{
				{Node: "<", Children: nil},
				{Node: "Type", Children: []*graph.Tree{
					{Node: "type: Int", Children: nil},
					{Node: "Gen", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
				{Node: ">", Children: nil},
			},
		}},
		"nested generic type": {input: "<List<Int>>", expected: graph.Tree{
			Node: "Gen",
			Children: []*graph.Tree{
				{Node: "<", Children: nil},
				{Node: "Type", Children: []*graph.Tree{
					{Node: "type: List", Children: nil},
					{Node: "Gen", Children: []*graph.Tree{
						{Node: "<", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: Int", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
						{Node: ">", Children: nil},
					}},
				}},
				{Node: ">", Children: nil},
			},
		}},
	})
}

func TestNoParseType(t *testing.T) {
	Parser(ParseType).testTableFails(t, map[string]string{
		"wrong generic order": "<generic>type",
	})
}

func TestParseType(t *testing.T) {
	Parser(ParseType).testTableSuccess(t, map[string]test{
		"parse simple type": {input: "Int", expected: graph.Tree{
			Node: "Type",
			Children: []*graph.Tree{
				{Node: "type: Int", Children: nil},
				{Node: "Gen", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
			},
		}},
		"parse generic type": {input: "List<Int>", expected: graph.Tree{
			Node: "Type",
			Children: []*graph.Tree{
				{Node: "type: List", Children: nil},
				{Node: "Gen", Children: []*graph.Tree{
					{Node: "<", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: Int", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
					{Node: ">", Children: nil},
				}},
			},
		}},
	})
}

func TestNoParseFType(t *testing.T) {
	Parser(ParseFType).testTableFails(t, map[string]string{
		"empty type":              ":",
		"strange symbol in type:": ": 0ops",
	})
}

func TestParseFType(t *testing.T) {
	Parser(ParseFType).testTableSuccess(t, map[string]test{
		"parse empty ftype": {input: "\t ", expected: graph.Tree{
			Node: "FType",
			Children: []*graph.Tree{
				{Node: "eps", Children: nil},
			},
		}},
		"parse simple ftype": {input: ": Int", expected: graph.Tree{
			Node: "FType",
			Children: []*graph.Tree{
				{Node: ":", Children: nil},
				{Node: "Type", Children: []*graph.Tree{
					{Node: "type: Int", Children: nil},
					{Node: "Gen", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
			},
		}},
		"parse generic ftype": {input: ": List<Int>", expected: graph.Tree{
			Node: "FType",
			Children: []*graph.Tree{
				{Node: ":", Children: nil},
				{Node: "Type", Children: []*graph.Tree{
					{Node: "type: List", Children: nil},
					{Node: "Gen", Children: []*graph.Tree{
						{Node: "<", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: Int", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
						{Node: ">", Children: nil},
					}},
				}},
			},
		}},
	})
}

func TestNoParseArg(t *testing.T) {
	Parser(ParseArg).testTableFails(t, map[string]string{
		"empty type":   "name:",
		"empty name":   ":type",
		"no doubledot": "name type",
	})
}

func TestParseArg(t *testing.T) {
	Parser(ParseArg).testTableSuccess(t, map[string]test{
		"simple arg": {input: "name : type", expected: graph.Tree{
			Node: "Arg",
			Children: []*graph.Tree{
				{Node: "name: name", Children: nil},
				{Node: ":", Children: nil},
				{Node: "Type", Children: []*graph.Tree{
					{Node: "type: type", Children: nil},
					{Node: "Gen", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
			},
		}},
	})
}

func TestNoParseDefArg(t *testing.T) {
	Parser(ParseDefArg).testTableFails(t, map[string]string{
		"non-default arg":           ", name : type",
		"non-default after default": ", name : type = value, name : type",
	})
}

func TestParseDefArg(t *testing.T) {
	Parser(ParseDefArg).testTableSuccess(t, map[string]test{
		"empty arg": {input: "\t ", expected: graph.Tree{
			Node: "DefArg",
			Children: []*graph.Tree{
				{Node: "eps", Children: nil},
			},
		}},
		"one arg": {input: ", name : type = value", expected: graph.Tree{
			Node: "DefArg",
			Children: []*graph.Tree{
				{Node: ",", Children: nil},
				{Node: "Arg", Children: []*graph.Tree{
					{Node: "name: name", Children: nil},
					{Node: ":", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: type", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: "=", Children: nil},
				{Node: "value: value", Children: nil},
				{Node: "DefArg", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
			},
		}},
		"two args": {input: ",name1:type1=value1, name2 : type2 = value2", expected: graph.Tree{
			Node: "DefArg",
			Children: []*graph.Tree{
				{Node: ",", Children: nil},
				{Node: "Arg", Children: []*graph.Tree{
					{Node: "name: name1", Children: nil},
					{Node: ":", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: type1", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: "=", Children: nil},
				{Node: "value: value1", Children: nil},
				{Node: "DefArg", Children: []*graph.Tree{
					{Node: ",", Children: nil},
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: name2", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: type2", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "=", Children: nil},
					{Node: "value: value2", Children: nil},
					{Node: "DefArg", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
			},
		}},
	})
}

func TestNoParseTail(t *testing.T) {
	Parser(ParseTail).testTableFails(t, map[string]string{
		"non-default after default": " = value, name : type",
	})
}

func TestParseTail(t *testing.T) {
	Parser(ParseTail).testTableSuccess(t, map[string]test{
		"empty tail": {input: "\t ", expected: graph.Tree{
			Node: "Tail",
			Children: []*graph.Tree{
				{Node: "eps", Children: nil},
			},
		}},
		"empty def arg tail": {input: "= val", expected: graph.Tree{
			Node: "Tail",
			Children: []*graph.Tree{
				{Node: "=", Children: nil},
				{Node: "value: val", Children: nil},
				{Node: "DefArg", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
			},
		}},
		"def arg tail": {input: "= val, name : type = value", expected: graph.Tree{
			Node: "Tail",
			Children: []*graph.Tree{
				{Node: "=", Children: nil},
				{Node: "value: val", Children: nil},
				{Node: "DefArg", Children: []*graph.Tree{
					{Node: ",", Children: nil},
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: name", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: type", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "=", Children: nil},
					{Node: "value: value", Children: nil},
					{Node: "DefArg", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
			},
		}},
		"usual arg tail": {input: ", name : type", expected: graph.Tree{
			Node: "Tail",
			Children: []*graph.Tree{
				{Node: ",", Children: nil},
				{Node: "Arg", Children: []*graph.Tree{
					{Node: "name: name", Children: nil},
					{Node: ":", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: type", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: "Tail", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
			},
		}},
		"arg and then def arg": {input: ", name : type, name : type = value", expected: graph.Tree{
			Node: "Tail",
			Children: []*graph.Tree{
				{Node: ",", Children: nil},
				{Node: "Arg", Children: []*graph.Tree{
					{Node: "name: name", Children: nil},
					{Node: ":", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: type", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: "Tail", Children: []*graph.Tree{
					{Node: ",", Children: nil},
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: name", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: type", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "Tail", Children: []*graph.Tree{
						{Node: "=", Children: nil},
						{Node: "value: value", Children: nil},
						{Node: "DefArg", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
			},
		}},
	})
}
