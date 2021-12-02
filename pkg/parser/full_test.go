package parser

import (
	"testing"

	"mt-2/pkg/graph"
)

func TestNoParseFun(t *testing.T) {
	Parser(parseFun).testTableFails(t, map[string]string{
		"empty input":                  "   ",
		"invalid fun name":             "fun 1name() : Unit",
		"invalid args declaration":     "fun name(arg1 : type, arg2 type) : Unit",
		"go-style function 1":          "func name()",
		"go-style function 2":          "fun name(a, b, c : type)",
		"go-style function 3":          "fun name(arg : type) type",
		"go-style function 4":          "fun name() : (type, error)",
		"non-empty string after parse": "fun name() : type HERO GOES TAIL",
		"strange type sequence":        "fun name(arg : type : what) : Unit",
		"coma not followed by arg":     "fun name(arg: type,) : Unit",
	})
}

func TestParseFun(t *testing.T) {
	Parser(parseFun).testTableSuccess(t, map[string]test{
		"simple function": {"fun funName(argName : argType, otherName : otherType) : returnType", graph.Tree{
			Node: "Fun",
			Children: []*graph.Tree{
				{Node: "fun", Children: nil},
				{Node: "name: funName", Children: nil},
				{Node: "(", Children: nil},
				{Node: "Args", Children: []*graph.Tree{
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: argName", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: argType", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "Tail", Children: []*graph.Tree{
						{Node: ",", Children: nil},
						{Node: "Arg", Children: []*graph.Tree{
							{Node: "name: otherName", Children: nil},
							{Node: ":", Children: nil},
							{Node: "Type", Children: []*graph.Tree{
								{Node: "type: otherType", Children: nil},
								{Node: "Gen", Children: []*graph.Tree{
									{Node: "eps", Children: nil},
								}},
							}},
						}},
						{Node: "Tail", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: ")", Children: nil},
				{Node: "FType", Children: []*graph.Tree{
					{Node: ":", Children: nil},
					{Node: "Type", Children: []*graph.Tree{
						{Node: "type: returnType", Children: nil},
						{Node: "Gen", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: "eps", Children: nil},
			},
		}},
		"function with generics in return type": {"fun f() : List<Int>", graph.Tree{
			Node: "Fun",
			Children: []*graph.Tree{
				{Node: "fun", Children: nil},
				{Node: "name: f", Children: nil},
				{Node: "(", Children: nil},
				{Node: "Args", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
				{Node: ")", Children: nil},
				{Node: "FType", Children: []*graph.Tree{
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
				}},
				{Node: "eps", Children: nil},
			},
		}},
		"function with generics in arg type": {"fun f(arg : Type<What>)", graph.Tree{
			Node: "Fun",
			Children: []*graph.Tree{
				{Node: "fun", Children: nil},
				{Node: "name: f", Children: nil},
				{Node: "(", Children: nil},
				{Node: "Args", Children: []*graph.Tree{
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: arg", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: Type", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "<", Children: nil},
								{Node: "Type", Children: []*graph.Tree{
									{Node: "type: What", Children: nil},
									{Node: "Gen", Children: []*graph.Tree{
										{Node: "eps", Children: nil},
									}},
								}},
								{Node: ">", Children: nil},
							}},
						}},
					}},
					{Node: "Tail", Children: []*graph.Tree{
						{Node: "eps", Children: nil},
					}},
				}},
				{Node: ")", Children: nil},
				{Node: "FType", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
				{Node: "eps", Children: nil},
			},
		}},
		"function with only default": {"fun f(arg: Int = def)", graph.Tree{
			Node: "Fun",
			Children: []*graph.Tree{
				{Node: "fun", Children: nil},
				{Node: "name: f", Children: nil},
				{Node: "(", Children: nil},
				{Node: "Args", Children: []*graph.Tree{
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: arg", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: Int", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "Tail", Children: []*graph.Tree{
						{Node: "=", Children: nil},
						{Node: "value: def", Children: nil},
						{Node: "DefArg", Children: []*graph.Tree{
							{Node: "eps", Children: nil},
						}},
					}},
				}},
				{Node: ")", Children: nil},
				{Node: "FType", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
				{Node: "eps", Children: nil},
			},
		}},
		"function with two defaults": {"fun f(arg: Int = def, gra: Tni = fed)", graph.Tree{
			Node: "Fun",
			Children: []*graph.Tree{
				{Node: "fun", Children: nil},
				{Node: "name: f", Children: nil},
				{Node: "(", Children: nil},
				{Node: "Args", Children: []*graph.Tree{
					{Node: "Arg", Children: []*graph.Tree{
						{Node: "name: arg", Children: nil},
						{Node: ":", Children: nil},
						{Node: "Type", Children: []*graph.Tree{
							{Node: "type: Int", Children: nil},
							{Node: "Gen", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
					{Node: "Tail", Children: []*graph.Tree{
						{Node: "=", Children: nil},
						{Node: "value: def", Children: nil},
						{Node: "DefArg", Children: []*graph.Tree{
							{Node: ",", Children: nil},
							{Node: "Arg", Children: []*graph.Tree{
								{Node: "name: gra", Children: nil},
								{Node: ":", Children: nil},
								{Node: "Type", Children: []*graph.Tree{
									{Node: "type: Tni", Children: nil},
									{Node: "Gen", Children: []*graph.Tree{
										{Node: "eps", Children: nil},
									}},
								}},
							}},
							{Node: "=", Children: nil},
							{Node: "DefArg", Children: []*graph.Tree{
								{Node: "eps", Children: nil},
							}},
						}},
					}},
				}},
				{Node: ")", Children: nil},
				{Node: "FType", Children: []*graph.Tree{
					{Node: "eps", Children: nil},
				}},
				{Node: "eps", Children: nil},
			},
		}},
	})
}
