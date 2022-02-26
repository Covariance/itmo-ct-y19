// Code generated from pkg/parser/GospodGrammar.g4 by ANTLR 4.9. DO NOT EDIT.

package parser

import (
	"fmt"
	"unicode"

	"github.com/antlr/antlr4/runtime/Go/antlr"
)

import str "parser-generator/pkg/structure"

// Suppress unused import error
var _ = str.Rule{}

// Suppress unused import error
var _ = fmt.Printf
var _ = unicode.IsLetter

var serializedLexerAtn = []uint16{
	3, 24715, 42794, 33075, 47597, 16764, 15335, 30598, 22884, 2, 18, 125,
	8, 1, 4, 2, 9, 2, 4, 3, 9, 3, 4, 4, 9, 4, 4, 5, 9, 5, 4, 6, 9, 6, 4, 7,
	9, 7, 4, 8, 9, 8, 4, 9, 9, 9, 4, 10, 9, 10, 4, 11, 9, 11, 4, 12, 9, 12,
	4, 13, 9, 13, 4, 14, 9, 14, 4, 15, 9, 15, 4, 16, 9, 16, 4, 17, 9, 17, 3,
	2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 3, 3, 3, 3, 4, 3,
	4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 5, 3, 5, 3,
	6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 7, 3, 7, 3, 7, 3, 7, 3, 7, 3,
	7, 3, 7, 3, 8, 3, 8, 3, 9, 3, 9, 3, 10, 3, 10, 3, 10, 3, 10, 3, 10, 3,
	10, 3, 10, 3, 10, 3, 11, 3, 11, 3, 12, 3, 12, 3, 13, 6, 13, 91, 10, 13,
	13, 13, 14, 13, 92, 3, 13, 3, 13, 3, 14, 6, 14, 98, 10, 14, 13, 14, 14,
	14, 99, 3, 15, 3, 15, 7, 15, 104, 10, 15, 12, 15, 14, 15, 107, 11, 15,
	3, 16, 3, 16, 7, 16, 111, 10, 16, 12, 16, 14, 16, 114, 11, 16, 3, 16, 3,
	16, 3, 17, 3, 17, 6, 17, 120, 10, 17, 13, 17, 14, 17, 121, 3, 17, 3, 17,
	2, 2, 18, 3, 3, 5, 4, 7, 5, 9, 6, 11, 7, 13, 8, 15, 9, 17, 10, 19, 11,
	21, 12, 23, 13, 25, 14, 27, 15, 29, 16, 31, 17, 33, 18, 3, 2, 8, 5, 2,
	11, 12, 15, 15, 34, 34, 3, 2, 50, 59, 4, 2, 67, 92, 99, 124, 6, 2, 50,
	59, 67, 92, 97, 97, 99, 124, 3, 2, 36, 36, 3, 2, 37, 37, 2, 129, 2, 3,
	3, 2, 2, 2, 2, 5, 3, 2, 2, 2, 2, 7, 3, 2, 2, 2, 2, 9, 3, 2, 2, 2, 2, 11,
	3, 2, 2, 2, 2, 13, 3, 2, 2, 2, 2, 15, 3, 2, 2, 2, 2, 17, 3, 2, 2, 2, 2,
	19, 3, 2, 2, 2, 2, 21, 3, 2, 2, 2, 2, 23, 3, 2, 2, 2, 2, 25, 3, 2, 2, 2,
	2, 27, 3, 2, 2, 2, 2, 29, 3, 2, 2, 2, 2, 31, 3, 2, 2, 2, 2, 33, 3, 2, 2,
	2, 3, 35, 3, 2, 2, 2, 5, 44, 3, 2, 2, 2, 7, 46, 3, 2, 2, 2, 9, 57, 3, 2,
	2, 2, 11, 59, 3, 2, 2, 2, 13, 66, 3, 2, 2, 2, 15, 73, 3, 2, 2, 2, 17, 75,
	3, 2, 2, 2, 19, 77, 3, 2, 2, 2, 21, 85, 3, 2, 2, 2, 23, 87, 3, 2, 2, 2,
	25, 90, 3, 2, 2, 2, 27, 97, 3, 2, 2, 2, 29, 101, 3, 2, 2, 2, 31, 108, 3,
	2, 2, 2, 33, 117, 3, 2, 2, 2, 35, 36, 7, 66, 2, 2, 36, 37, 7, 105, 2, 2,
	37, 38, 7, 116, 2, 2, 38, 39, 7, 99, 2, 2, 39, 40, 7, 111, 2, 2, 40, 41,
	7, 111, 2, 2, 41, 42, 7, 99, 2, 2, 42, 43, 7, 116, 2, 2, 43, 4, 3, 2, 2,
	2, 44, 45, 7, 61, 2, 2, 45, 6, 3, 2, 2, 2, 46, 47, 7, 66, 2, 2, 47, 48,
	7, 118, 2, 2, 48, 49, 7, 103, 2, 2, 49, 50, 7, 116, 2, 2, 50, 51, 7, 111,
	2, 2, 51, 52, 7, 107, 2, 2, 52, 53, 7, 112, 2, 2, 53, 54, 7, 99, 2, 2,
	54, 55, 7, 110, 2, 2, 55, 56, 7, 117, 2, 2, 56, 8, 3, 2, 2, 2, 57, 58,
	7, 60, 2, 2, 58, 10, 3, 2, 2, 2, 59, 60, 7, 66, 2, 2, 60, 61, 7, 117, 2,
	2, 61, 62, 7, 118, 2, 2, 62, 63, 7, 99, 2, 2, 63, 64, 7, 116, 2, 2, 64,
	65, 7, 118, 2, 2, 65, 12, 3, 2, 2, 2, 66, 67, 7, 66, 2, 2, 67, 68, 7, 116,
	2, 2, 68, 69, 7, 119, 2, 2, 69, 70, 7, 110, 2, 2, 70, 71, 7, 103, 2, 2,
	71, 72, 7, 117, 2, 2, 72, 14, 3, 2, 2, 2, 73, 74, 7, 93, 2, 2, 74, 16,
	3, 2, 2, 2, 75, 76, 7, 95, 2, 2, 76, 18, 3, 2, 2, 2, 77, 78, 7, 116, 2,
	2, 78, 79, 7, 103, 2, 2, 79, 80, 7, 118, 2, 2, 80, 81, 7, 119, 2, 2, 81,
	82, 7, 116, 2, 2, 82, 83, 7, 112, 2, 2, 83, 84, 7, 117, 2, 2, 84, 20, 3,
	2, 2, 2, 85, 86, 7, 126, 2, 2, 86, 22, 3, 2, 2, 2, 87, 88, 7, 46, 2, 2,
	88, 24, 3, 2, 2, 2, 89, 91, 9, 2, 2, 2, 90, 89, 3, 2, 2, 2, 91, 92, 3,
	2, 2, 2, 92, 90, 3, 2, 2, 2, 92, 93, 3, 2, 2, 2, 93, 94, 3, 2, 2, 2, 94,
	95, 8, 13, 2, 2, 95, 26, 3, 2, 2, 2, 96, 98, 9, 3, 2, 2, 97, 96, 3, 2,
	2, 2, 98, 99, 3, 2, 2, 2, 99, 97, 3, 2, 2, 2, 99, 100, 3, 2, 2, 2, 100,
	28, 3, 2, 2, 2, 101, 105, 9, 4, 2, 2, 102, 104, 9, 5, 2, 2, 103, 102, 3,
	2, 2, 2, 104, 107, 3, 2, 2, 2, 105, 103, 3, 2, 2, 2, 105, 106, 3, 2, 2,
	2, 106, 30, 3, 2, 2, 2, 107, 105, 3, 2, 2, 2, 108, 112, 7, 36, 2, 2, 109,
	111, 10, 6, 2, 2, 110, 109, 3, 2, 2, 2, 111, 114, 3, 2, 2, 2, 112, 110,
	3, 2, 2, 2, 112, 113, 3, 2, 2, 2, 113, 115, 3, 2, 2, 2, 114, 112, 3, 2,
	2, 2, 115, 116, 7, 36, 2, 2, 116, 32, 3, 2, 2, 2, 117, 119, 7, 37, 2, 2,
	118, 120, 10, 7, 2, 2, 119, 118, 3, 2, 2, 2, 120, 121, 3, 2, 2, 2, 121,
	119, 3, 2, 2, 2, 121, 122, 3, 2, 2, 2, 122, 123, 3, 2, 2, 2, 123, 124,
	7, 37, 2, 2, 124, 34, 3, 2, 2, 2, 8, 2, 92, 99, 105, 112, 121, 3, 8, 2,
	2,
}

var lexerChannelNames = []string{
	"DEFAULT_TOKEN_CHANNEL", "HIDDEN",
}

var lexerModeNames = []string{
	"DEFAULT_MODE",
}

var lexerLiteralNames = []string{
	"", "'@grammar'", "';'", "'@terminals'", "':'", "'@start'", "'@rules'",
	"'['", "']'", "'returns'", "'|'", "','",
}

var lexerSymbolicNames = []string{
	"", "", "", "", "", "", "", "", "", "", "", "", "SKIP_WHITESPACES", "INT",
	"NAME", "REGEXP", "SOURCE_CODE",
}

var lexerRuleNames = []string{
	"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8",
	"T__9", "T__10", "SKIP_WHITESPACES", "INT", "NAME", "REGEXP", "SOURCE_CODE",
}

type GospodGrammarLexer struct {
	*antlr.BaseLexer
	channelNames []string
	modeNames    []string
	// TODO: EOF string
}

// NewGospodGrammarLexer produces a new lexer instance for the optional input antlr.CharStream.
//
// The *GospodGrammarLexer instance produced may be reused by calling the SetInputStream method.
// The initial lexer configuration is expensive to construct, and the object is not thread-safe;
// however, if used within a Golang sync.Pool, the construction cost amortizes well and the
// objects can be used in a thread-safe manner.
func NewGospodGrammarLexer(input antlr.CharStream) *GospodGrammarLexer {
	l := new(GospodGrammarLexer)
	lexerDeserializer := antlr.NewATNDeserializer(nil)
	lexerAtn := lexerDeserializer.DeserializeFromUInt16(serializedLexerAtn)
	lexerDecisionToDFA := make([]*antlr.DFA, len(lexerAtn.DecisionToState))
	for index, ds := range lexerAtn.DecisionToState {
		lexerDecisionToDFA[index] = antlr.NewDFA(ds, index)
	}
	l.BaseLexer = antlr.NewBaseLexer(input)
	l.Interpreter = antlr.NewLexerATNSimulator(l, lexerAtn, lexerDecisionToDFA, antlr.NewPredictionContextCache())

	l.channelNames = lexerChannelNames
	l.modeNames = lexerModeNames
	l.RuleNames = lexerRuleNames
	l.LiteralNames = lexerLiteralNames
	l.SymbolicNames = lexerSymbolicNames
	l.GrammarFileName = "GospodGrammar.g4"
	// TODO: l.EOF = antlr.TokenEOF

	return l
}

// GospodGrammarLexer tokens.
const (
	GospodGrammarLexerT__0             = 1
	GospodGrammarLexerT__1             = 2
	GospodGrammarLexerT__2             = 3
	GospodGrammarLexerT__3             = 4
	GospodGrammarLexerT__4             = 5
	GospodGrammarLexerT__5             = 6
	GospodGrammarLexerT__6             = 7
	GospodGrammarLexerT__7             = 8
	GospodGrammarLexerT__8             = 9
	GospodGrammarLexerT__9             = 10
	GospodGrammarLexerT__10            = 11
	GospodGrammarLexerSKIP_WHITESPACES = 12
	GospodGrammarLexerINT              = 13
	GospodGrammarLexerNAME             = 14
	GospodGrammarLexerREGEXP           = 15
	GospodGrammarLexerSOURCE_CODE      = 16
)
