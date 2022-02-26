// Code generated from pkg/parser/GospodGrammar.g4 by ANTLR 4.9. DO NOT EDIT.

package parser // GospodGrammar

import (
	"fmt"
	"reflect"
	"strconv"

	"github.com/antlr/antlr4/runtime/Go/antlr"
)

import str "parser-generator/pkg/structure"

// Suppress unused import error
var _ = str.Rule{}

// Suppress unused import errors
var _ = fmt.Printf
var _ = reflect.Copy
var _ = strconv.Itoa

var parserATN = []uint16{
	3, 24715, 42794, 33075, 47597, 16764, 15335, 30598, 22884, 3, 18, 151,
	4, 2, 9, 2, 4, 3, 9, 3, 4, 4, 9, 4, 4, 5, 9, 5, 4, 6, 9, 6, 4, 7, 9, 7,
	4, 8, 9, 8, 4, 9, 9, 9, 4, 10, 9, 10, 4, 11, 9, 11, 4, 12, 9, 12, 4, 13,
	9, 13, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4,
	3, 4, 7, 4, 39, 10, 4, 12, 4, 14, 4, 42, 11, 4, 3, 5, 3, 5, 3, 5, 3, 5,
	3, 5, 3, 5, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 7, 3, 7, 3, 7, 3, 7,
	6, 7, 60, 10, 7, 13, 7, 14, 7, 61, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8,
	5, 8, 70, 10, 8, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 5, 8, 77, 10, 8, 3, 8, 3,
	8, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 3, 8, 5, 8, 87, 10, 8, 7, 8, 89, 10, 8,
	12, 8, 14, 8, 92, 11, 8, 3, 8, 3, 8, 3, 9, 3, 9, 3, 9, 3, 9, 3, 9, 3, 9,
	3, 9, 7, 9, 103, 10, 9, 12, 9, 14, 9, 106, 11, 9, 3, 10, 3, 10, 3, 10,
	3, 10, 3, 10, 3, 10, 3, 10, 7, 10, 115, 10, 10, 12, 10, 14, 10, 118, 11,
	10, 3, 11, 3, 11, 3, 11, 3, 11, 3, 11, 3, 11, 5, 11, 126, 10, 11, 3, 11,
	3, 11, 3, 11, 5, 11, 131, 10, 11, 3, 11, 6, 11, 134, 10, 11, 13, 11, 14,
	11, 135, 3, 12, 3, 12, 3, 12, 3, 12, 3, 12, 7, 12, 143, 10, 12, 12, 12,
	14, 12, 146, 11, 12, 3, 13, 3, 13, 3, 13, 3, 13, 2, 2, 14, 2, 4, 6, 8,
	10, 12, 14, 16, 18, 20, 22, 24, 2, 2, 2, 150, 2, 26, 3, 2, 2, 2, 4, 31,
	3, 2, 2, 2, 6, 36, 3, 2, 2, 2, 8, 43, 3, 2, 2, 2, 10, 49, 3, 2, 2, 2, 12,
	55, 3, 2, 2, 2, 14, 63, 3, 2, 2, 2, 16, 95, 3, 2, 2, 2, 18, 107, 3, 2,
	2, 2, 20, 133, 3, 2, 2, 2, 22, 137, 3, 2, 2, 2, 24, 147, 3, 2, 2, 2, 26,
	27, 5, 4, 3, 2, 27, 28, 5, 6, 4, 2, 28, 29, 5, 10, 6, 2, 29, 30, 5, 12,
	7, 2, 30, 3, 3, 2, 2, 2, 31, 32, 7, 3, 2, 2, 32, 33, 7, 16, 2, 2, 33, 34,
	8, 3, 1, 2, 34, 35, 7, 4, 2, 2, 35, 5, 3, 2, 2, 2, 36, 40, 7, 5, 2, 2,
	37, 39, 5, 8, 5, 2, 38, 37, 3, 2, 2, 2, 39, 42, 3, 2, 2, 2, 40, 38, 3,
	2, 2, 2, 40, 41, 3, 2, 2, 2, 41, 7, 3, 2, 2, 2, 42, 40, 3, 2, 2, 2, 43,
	44, 7, 16, 2, 2, 44, 45, 7, 6, 2, 2, 45, 46, 7, 17, 2, 2, 46, 47, 7, 4,
	2, 2, 47, 48, 8, 5, 1, 2, 48, 9, 3, 2, 2, 2, 49, 50, 7, 7, 2, 2, 50, 51,
	7, 6, 2, 2, 51, 52, 7, 16, 2, 2, 52, 53, 8, 6, 1, 2, 53, 54, 7, 4, 2, 2,
	54, 11, 3, 2, 2, 2, 55, 59, 7, 8, 2, 2, 56, 57, 5, 14, 8, 2, 57, 58, 8,
	7, 1, 2, 58, 60, 3, 2, 2, 2, 59, 56, 3, 2, 2, 2, 60, 61, 3, 2, 2, 2, 61,
	59, 3, 2, 2, 2, 61, 62, 3, 2, 2, 2, 62, 13, 3, 2, 2, 2, 63, 64, 7, 16,
	2, 2, 64, 69, 8, 8, 1, 2, 65, 66, 7, 9, 2, 2, 66, 67, 5, 16, 9, 2, 67,
	68, 7, 10, 2, 2, 68, 70, 3, 2, 2, 2, 69, 65, 3, 2, 2, 2, 69, 70, 3, 2,
	2, 2, 70, 76, 3, 2, 2, 2, 71, 72, 7, 11, 2, 2, 72, 73, 7, 9, 2, 2, 73,
	74, 5, 18, 10, 2, 74, 75, 7, 10, 2, 2, 75, 77, 3, 2, 2, 2, 76, 71, 3, 2,
	2, 2, 76, 77, 3, 2, 2, 2, 77, 78, 3, 2, 2, 2, 78, 79, 7, 6, 2, 2, 79, 80,
	5, 20, 11, 2, 80, 90, 8, 8, 1, 2, 81, 86, 7, 12, 2, 2, 82, 83, 5, 20, 11,
	2, 83, 84, 8, 8, 1, 2, 84, 87, 3, 2, 2, 2, 85, 87, 8, 8, 1, 2, 86, 82,
	3, 2, 2, 2, 86, 85, 3, 2, 2, 2, 87, 89, 3, 2, 2, 2, 88, 81, 3, 2, 2, 2,
	89, 92, 3, 2, 2, 2, 90, 88, 3, 2, 2, 2, 90, 91, 3, 2, 2, 2, 91, 93, 3,
	2, 2, 2, 92, 90, 3, 2, 2, 2, 93, 94, 7, 4, 2, 2, 94, 15, 3, 2, 2, 2, 95,
	96, 7, 16, 2, 2, 96, 97, 7, 16, 2, 2, 97, 104, 8, 9, 1, 2, 98, 99, 7, 13,
	2, 2, 99, 100, 7, 16, 2, 2, 100, 101, 7, 16, 2, 2, 101, 103, 8, 9, 1, 2,
	102, 98, 3, 2, 2, 2, 103, 106, 3, 2, 2, 2, 104, 102, 3, 2, 2, 2, 104, 105,
	3, 2, 2, 2, 105, 17, 3, 2, 2, 2, 106, 104, 3, 2, 2, 2, 107, 108, 7, 16,
	2, 2, 108, 109, 7, 16, 2, 2, 109, 116, 8, 10, 1, 2, 110, 111, 7, 13, 2,
	2, 111, 112, 7, 16, 2, 2, 112, 113, 7, 16, 2, 2, 113, 115, 8, 10, 1, 2,
	114, 110, 3, 2, 2, 2, 115, 118, 3, 2, 2, 2, 116, 114, 3, 2, 2, 2, 116,
	117, 3, 2, 2, 2, 117, 19, 3, 2, 2, 2, 118, 116, 3, 2, 2, 2, 119, 125, 7,
	16, 2, 2, 120, 121, 7, 9, 2, 2, 121, 122, 5, 22, 12, 2, 122, 123, 8, 11,
	1, 2, 123, 124, 7, 10, 2, 2, 124, 126, 3, 2, 2, 2, 125, 120, 3, 2, 2, 2,
	125, 126, 3, 2, 2, 2, 126, 130, 3, 2, 2, 2, 127, 128, 5, 24, 13, 2, 128,
	129, 8, 11, 1, 2, 129, 131, 3, 2, 2, 2, 130, 127, 3, 2, 2, 2, 130, 131,
	3, 2, 2, 2, 131, 132, 3, 2, 2, 2, 132, 134, 8, 11, 1, 2, 133, 119, 3, 2,
	2, 2, 134, 135, 3, 2, 2, 2, 135, 133, 3, 2, 2, 2, 135, 136, 3, 2, 2, 2,
	136, 21, 3, 2, 2, 2, 137, 138, 7, 16, 2, 2, 138, 144, 8, 12, 1, 2, 139,
	140, 7, 13, 2, 2, 140, 141, 7, 16, 2, 2, 141, 143, 8, 12, 1, 2, 142, 139,
	3, 2, 2, 2, 143, 146, 3, 2, 2, 2, 144, 142, 3, 2, 2, 2, 144, 145, 3, 2,
	2, 2, 145, 23, 3, 2, 2, 2, 146, 144, 3, 2, 2, 2, 147, 148, 7, 18, 2, 2,
	148, 149, 8, 13, 1, 2, 149, 25, 3, 2, 2, 2, 14, 40, 61, 69, 76, 86, 90,
	104, 116, 125, 130, 135, 144,
}
var literalNames = []string{
	"", "'@grammar'", "';'", "'@terminals'", "':'", "'@start'", "'@rules'",
	"'['", "']'", "'returns'", "'|'", "','",
}
var symbolicNames = []string{
	"", "", "", "", "", "", "", "", "", "", "", "", "SKIP_WHITESPACES", "INT",
	"NAME", "REGEXP", "SOURCE_CODE",
}

var ruleNames = []string{
	"gram", "header", "terminals", "terminal_rule", "start_state", "nonterminals",
	"nonterminal", "nonterminal_params", "nonterminal_returns", "nonterm_rule",
	"rule_params", "rule_code",
}

type GospodGrammarParser struct {
	*antlr.BaseParser
}

// NewGospodGrammarParser produces a new parser instance for the optional input antlr.TokenStream.
//
// The *GospodGrammarParser instance produced may be reused by calling the SetInputStream method.
// The initial parser configuration is expensive to construct, and the object is not thread-safe;
// however, if used within a Golang sync.Pool, the construction cost amortizes well and the
// objects can be used in a thread-safe manner.
func NewGospodGrammarParser(input antlr.TokenStream) *GospodGrammarParser {
	this := new(GospodGrammarParser)
	deserializer := antlr.NewATNDeserializer(nil)
	deserializedATN := deserializer.DeserializeFromUInt16(parserATN)
	decisionToDFA := make([]*antlr.DFA, len(deserializedATN.DecisionToState))
	for index, ds := range deserializedATN.DecisionToState {
		decisionToDFA[index] = antlr.NewDFA(ds, index)
	}
	this.BaseParser = antlr.NewBaseParser(input)

	this.Interpreter = antlr.NewParserATNSimulator(this, deserializedATN, decisionToDFA, antlr.NewPredictionContextCache())
	this.RuleNames = ruleNames
	this.LiteralNames = literalNames
	this.SymbolicNames = symbolicNames
	this.GrammarFileName = "GospodGrammar.g4"

	return this
}

// GospodGrammarParser tokens.
const (
	GospodGrammarParserEOF              = antlr.TokenEOF
	GospodGrammarParserT__0             = 1
	GospodGrammarParserT__1             = 2
	GospodGrammarParserT__2             = 3
	GospodGrammarParserT__3             = 4
	GospodGrammarParserT__4             = 5
	GospodGrammarParserT__5             = 6
	GospodGrammarParserT__6             = 7
	GospodGrammarParserT__7             = 8
	GospodGrammarParserT__8             = 9
	GospodGrammarParserT__9             = 10
	GospodGrammarParserT__10            = 11
	GospodGrammarParserSKIP_WHITESPACES = 12
	GospodGrammarParserINT              = 13
	GospodGrammarParserNAME             = 14
	GospodGrammarParserREGEXP           = 15
	GospodGrammarParserSOURCE_CODE      = 16
)

// GospodGrammarParser rules.
const (
	GospodGrammarParserRULE_gram                = 0
	GospodGrammarParserRULE_header              = 1
	GospodGrammarParserRULE_terminals           = 2
	GospodGrammarParserRULE_terminal_rule       = 3
	GospodGrammarParserRULE_start_state         = 4
	GospodGrammarParserRULE_nonterminals        = 5
	GospodGrammarParserRULE_nonterminal         = 6
	GospodGrammarParserRULE_nonterminal_params  = 7
	GospodGrammarParserRULE_nonterminal_returns = 8
	GospodGrammarParserRULE_nonterm_rule        = 9
	GospodGrammarParserRULE_rule_params         = 10
	GospodGrammarParserRULE_rule_code           = 11
)

// IGramContext is an interface to support dynamic dispatch.
type IGramContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsGramContext differentiates from other interfaces.
	IsGramContext()
}

type GramContext struct {
	*antlr.BaseParserRuleContext
	parser antlr.Parser
	g      *str.Grammar
}

func NewEmptyGramContext() *GramContext {
	var p = new(GramContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_gram
	return p
}

func (*GramContext) IsGramContext() {}

func NewGramContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *GramContext {
	var p = new(GramContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_gram

	p.g = g

	return p
}

func (s *GramContext) GetParser() antlr.Parser { return s.parser }

func (s *GramContext) GetG() *str.Grammar { return s.g }

func (s *GramContext) SetG(v *str.Grammar) { s.g = v }

func (s *GramContext) Header() IHeaderContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*IHeaderContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(IHeaderContext)
}

func (s *GramContext) Terminals() ITerminalsContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*ITerminalsContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(ITerminalsContext)
}

func (s *GramContext) Start_state() IStart_stateContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*IStart_stateContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(IStart_stateContext)
}

func (s *GramContext) Nonterminals() INonterminalsContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*INonterminalsContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(INonterminalsContext)
}

func (s *GramContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *GramContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *GramContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterGram(s)
	}
}

func (s *GramContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitGram(s)
	}
}

func (p *GospodGrammarParser) Gram(g *str.Grammar) (localctx IGramContext) {
	localctx = NewGramContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 0, GospodGrammarParserRULE_gram)
	localctx.(*GramContext).g = &str.Grammar{}

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(24)
		p.Header(g)
	}
	{
		p.SetState(25)
		p.Terminals(g)
	}
	{
		p.SetState(26)
		p.Start_state(g)
	}
	{
		p.SetState(27)
		p.Nonterminals(g)
	}

	return localctx
}

// IHeaderContext is an interface to support dynamic dispatch.
type IHeaderContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_NAME returns the _NAME token.
	Get_NAME() antlr.Token

	// Set_NAME sets the _NAME token.
	Set_NAME(antlr.Token)

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsHeaderContext differentiates from other interfaces.
	IsHeaderContext()
}

type HeaderContext struct {
	*antlr.BaseParserRuleContext
	parser antlr.Parser
	g      *str.Grammar
	_NAME  antlr.Token
}

func NewEmptyHeaderContext() *HeaderContext {
	var p = new(HeaderContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_header
	return p
}

func (*HeaderContext) IsHeaderContext() {}

func NewHeaderContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *HeaderContext {
	var p = new(HeaderContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_header

	p.g = g

	return p
}

func (s *HeaderContext) GetParser() antlr.Parser { return s.parser }

func (s *HeaderContext) Get_NAME() antlr.Token { return s._NAME }

func (s *HeaderContext) Set_NAME(v antlr.Token) { s._NAME = v }

func (s *HeaderContext) GetG() *str.Grammar { return s.g }

func (s *HeaderContext) SetG(v *str.Grammar) { s.g = v }

func (s *HeaderContext) NAME() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, 0)
}

func (s *HeaderContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *HeaderContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *HeaderContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterHeader(s)
	}
}

func (s *HeaderContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitHeader(s)
	}
}

func (p *GospodGrammarParser) Header(g *str.Grammar) (localctx IHeaderContext) {
	localctx = NewHeaderContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 2, GospodGrammarParserRULE_header)

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(29)
		p.Match(GospodGrammarParserT__0)
	}
	{
		p.SetState(30)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*HeaderContext)._NAME = _m
	}
	localctx.(*HeaderContext).g.Name = (func() string {
		if localctx.(*HeaderContext).Get_NAME() == nil {
			return ""
		} else {
			return localctx.(*HeaderContext).Get_NAME().GetText()
		}
	}())
	{
		p.SetState(32)
		p.Match(GospodGrammarParserT__1)
	}

	return localctx
}

// ITerminalsContext is an interface to support dynamic dispatch.
type ITerminalsContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsTerminalsContext differentiates from other interfaces.
	IsTerminalsContext()
}

type TerminalsContext struct {
	*antlr.BaseParserRuleContext
	parser antlr.Parser
	g      *str.Grammar
}

func NewEmptyTerminalsContext() *TerminalsContext {
	var p = new(TerminalsContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_terminals
	return p
}

func (*TerminalsContext) IsTerminalsContext() {}

func NewTerminalsContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *TerminalsContext {
	var p = new(TerminalsContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_terminals

	p.g = g

	return p
}

func (s *TerminalsContext) GetParser() antlr.Parser { return s.parser }

func (s *TerminalsContext) GetG() *str.Grammar { return s.g }

func (s *TerminalsContext) SetG(v *str.Grammar) { s.g = v }

func (s *TerminalsContext) AllTerminal_rule() []ITerminal_ruleContext {
	var ts = s.GetTypedRuleContexts(reflect.TypeOf((*ITerminal_ruleContext)(nil)).Elem())
	var tst = make([]ITerminal_ruleContext, len(ts))

	for i, t := range ts {
		if t != nil {
			tst[i] = t.(ITerminal_ruleContext)
		}
	}

	return tst
}

func (s *TerminalsContext) Terminal_rule(i int) ITerminal_ruleContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*ITerminal_ruleContext)(nil)).Elem(), i)

	if t == nil {
		return nil
	}

	return t.(ITerminal_ruleContext)
}

func (s *TerminalsContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *TerminalsContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *TerminalsContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterTerminals(s)
	}
}

func (s *TerminalsContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitTerminals(s)
	}
}

func (p *GospodGrammarParser) Terminals(g *str.Grammar) (localctx ITerminalsContext) {
	localctx = NewTerminalsContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 4, GospodGrammarParserRULE_terminals)
	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(34)
		p.Match(GospodGrammarParserT__2)
	}
	p.SetState(38)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for _la == GospodGrammarParserNAME {
		{
			p.SetState(35)
			p.Terminal_rule(g)
		}

		p.SetState(40)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// ITerminal_ruleContext is an interface to support dynamic dispatch.
type ITerminal_ruleContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_NAME returns the _NAME token.
	Get_NAME() antlr.Token

	// Get_REGEXP returns the _REGEXP token.
	Get_REGEXP() antlr.Token

	// Set_NAME sets the _NAME token.
	Set_NAME(antlr.Token)

	// Set_REGEXP sets the _REGEXP token.
	Set_REGEXP(antlr.Token)

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsTerminal_ruleContext differentiates from other interfaces.
	IsTerminal_ruleContext()
}

type Terminal_ruleContext struct {
	*antlr.BaseParserRuleContext
	parser  antlr.Parser
	g       *str.Grammar
	_NAME   antlr.Token
	_REGEXP antlr.Token
}

func NewEmptyTerminal_ruleContext() *Terminal_ruleContext {
	var p = new(Terminal_ruleContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_terminal_rule
	return p
}

func (*Terminal_ruleContext) IsTerminal_ruleContext() {}

func NewTerminal_ruleContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *Terminal_ruleContext {
	var p = new(Terminal_ruleContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_terminal_rule

	p.g = g

	return p
}

func (s *Terminal_ruleContext) GetParser() antlr.Parser { return s.parser }

func (s *Terminal_ruleContext) Get_NAME() antlr.Token { return s._NAME }

func (s *Terminal_ruleContext) Get_REGEXP() antlr.Token { return s._REGEXP }

func (s *Terminal_ruleContext) Set_NAME(v antlr.Token) { s._NAME = v }

func (s *Terminal_ruleContext) Set_REGEXP(v antlr.Token) { s._REGEXP = v }

func (s *Terminal_ruleContext) GetG() *str.Grammar { return s.g }

func (s *Terminal_ruleContext) SetG(v *str.Grammar) { s.g = v }

func (s *Terminal_ruleContext) NAME() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, 0)
}

func (s *Terminal_ruleContext) REGEXP() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserREGEXP, 0)
}

func (s *Terminal_ruleContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Terminal_ruleContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Terminal_ruleContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterTerminal_rule(s)
	}
}

func (s *Terminal_ruleContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitTerminal_rule(s)
	}
}

func (p *GospodGrammarParser) Terminal_rule(g *str.Grammar) (localctx ITerminal_ruleContext) {
	localctx = NewTerminal_ruleContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 6, GospodGrammarParserRULE_terminal_rule)

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(41)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Terminal_ruleContext)._NAME = _m
	}
	{
		p.SetState(42)
		p.Match(GospodGrammarParserT__3)
	}
	{
		p.SetState(43)

		var _m = p.Match(GospodGrammarParserREGEXP)

		localctx.(*Terminal_ruleContext)._REGEXP = _m
	}
	{
		p.SetState(44)
		p.Match(GospodGrammarParserT__1)
	}

	localctx.(*Terminal_ruleContext).g.AddTerminal((func() string {
		if localctx.(*Terminal_ruleContext).Get_NAME() == nil {
			return ""
		} else {
			return localctx.(*Terminal_ruleContext).Get_NAME().GetText()
		}
	}()), (func() string {
		if localctx.(*Terminal_ruleContext).Get_REGEXP() == nil {
			return ""
		} else {
			return localctx.(*Terminal_ruleContext).Get_REGEXP().GetText()
		}
	}())[1:len((func() string {
		if localctx.(*Terminal_ruleContext).Get_REGEXP() == nil {
			return ""
		} else {
			return localctx.(*Terminal_ruleContext).Get_REGEXP().GetText()
		}
	}()))-1])

	return localctx
}

// IStart_stateContext is an interface to support dynamic dispatch.
type IStart_stateContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_NAME returns the _NAME token.
	Get_NAME() antlr.Token

	// Set_NAME sets the _NAME token.
	Set_NAME(antlr.Token)

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsStart_stateContext differentiates from other interfaces.
	IsStart_stateContext()
}

type Start_stateContext struct {
	*antlr.BaseParserRuleContext
	parser antlr.Parser
	g      *str.Grammar
	_NAME  antlr.Token
}

func NewEmptyStart_stateContext() *Start_stateContext {
	var p = new(Start_stateContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_start_state
	return p
}

func (*Start_stateContext) IsStart_stateContext() {}

func NewStart_stateContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *Start_stateContext {
	var p = new(Start_stateContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_start_state

	p.g = g

	return p
}

func (s *Start_stateContext) GetParser() antlr.Parser { return s.parser }

func (s *Start_stateContext) Get_NAME() antlr.Token { return s._NAME }

func (s *Start_stateContext) Set_NAME(v antlr.Token) { s._NAME = v }

func (s *Start_stateContext) GetG() *str.Grammar { return s.g }

func (s *Start_stateContext) SetG(v *str.Grammar) { s.g = v }

func (s *Start_stateContext) NAME() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, 0)
}

func (s *Start_stateContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Start_stateContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Start_stateContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterStart_state(s)
	}
}

func (s *Start_stateContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitStart_state(s)
	}
}

func (p *GospodGrammarParser) Start_state(g *str.Grammar) (localctx IStart_stateContext) {
	localctx = NewStart_stateContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 8, GospodGrammarParserRULE_start_state)

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(47)
		p.Match(GospodGrammarParserT__4)
	}
	{
		p.SetState(48)
		p.Match(GospodGrammarParserT__3)
	}
	{
		p.SetState(49)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Start_stateContext)._NAME = _m
	}
	localctx.(*Start_stateContext).g.Start = (func() string {
		if localctx.(*Start_stateContext).Get_NAME() == nil {
			return ""
		} else {
			return localctx.(*Start_stateContext).Get_NAME().GetText()
		}
	}())
	{
		p.SetState(51)
		p.Match(GospodGrammarParserT__1)
	}

	return localctx
}

// INonterminalsContext is an interface to support dynamic dispatch.
type INonterminalsContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_nonterminal returns the _nonterminal rule contexts.
	Get_nonterminal() INonterminalContext

	// Set_nonterminal sets the _nonterminal rule contexts.
	Set_nonterminal(INonterminalContext)

	// GetG returns the g attribute.
	GetG() *str.Grammar

	// SetG sets the g attribute.
	SetG(*str.Grammar)

	// IsNonterminalsContext differentiates from other interfaces.
	IsNonterminalsContext()
}

type NonterminalsContext struct {
	*antlr.BaseParserRuleContext
	parser       antlr.Parser
	g            *str.Grammar
	_nonterminal INonterminalContext
}

func NewEmptyNonterminalsContext() *NonterminalsContext {
	var p = new(NonterminalsContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_nonterminals
	return p
}

func (*NonterminalsContext) IsNonterminalsContext() {}

func NewNonterminalsContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, g *str.Grammar) *NonterminalsContext {
	var p = new(NonterminalsContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_nonterminals

	p.g = g

	return p
}

func (s *NonterminalsContext) GetParser() antlr.Parser { return s.parser }

func (s *NonterminalsContext) Get_nonterminal() INonterminalContext { return s._nonterminal }

func (s *NonterminalsContext) Set_nonterminal(v INonterminalContext) { s._nonterminal = v }

func (s *NonterminalsContext) GetG() *str.Grammar { return s.g }

func (s *NonterminalsContext) SetG(v *str.Grammar) { s.g = v }

func (s *NonterminalsContext) AllNonterminal() []INonterminalContext {
	var ts = s.GetTypedRuleContexts(reflect.TypeOf((*INonterminalContext)(nil)).Elem())
	var tst = make([]INonterminalContext, len(ts))

	for i, t := range ts {
		if t != nil {
			tst[i] = t.(INonterminalContext)
		}
	}

	return tst
}

func (s *NonterminalsContext) Nonterminal(i int) INonterminalContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*INonterminalContext)(nil)).Elem(), i)

	if t == nil {
		return nil
	}

	return t.(INonterminalContext)
}

func (s *NonterminalsContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *NonterminalsContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *NonterminalsContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterNonterminals(s)
	}
}

func (s *NonterminalsContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitNonterminals(s)
	}
}

func (p *GospodGrammarParser) Nonterminals(g *str.Grammar) (localctx INonterminalsContext) {
	localctx = NewNonterminalsContext(p, p.GetParserRuleContext(), p.GetState(), g)
	p.EnterRule(localctx, 10, GospodGrammarParserRULE_nonterminals)
	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(53)
		p.Match(GospodGrammarParserT__5)
	}
	p.SetState(57)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for ok := true; ok; ok = _la == GospodGrammarParserNAME {
		{
			p.SetState(54)

			var _x = p.Nonterminal()

			localctx.(*NonterminalsContext)._nonterminal = _x
		}
		localctx.(*NonterminalsContext).g.AddNonTerminal(*localctx.(*NonterminalsContext).Get_nonterminal().GetNonterm())

		p.SetState(59)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// INonterminalContext is an interface to support dynamic dispatch.
type INonterminalContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_NAME returns the _NAME token.
	Get_NAME() antlr.Token

	// Set_NAME sets the _NAME token.
	Set_NAME(antlr.Token)

	// GetR1 returns the r1 rule contexts.
	GetR1() INonterm_ruleContext

	// GetR2 returns the r2 rule contexts.
	GetR2() INonterm_ruleContext

	// SetR1 sets the r1 rule contexts.
	SetR1(INonterm_ruleContext)

	// SetR2 sets the r2 rule contexts.
	SetR2(INonterm_ruleContext)

	// GetNonterm returns the nonterm attribute.
	GetNonterm() *str.NonTerminal

	// SetNonterm sets the nonterm attribute.
	SetNonterm(*str.NonTerminal)

	// IsNonterminalContext differentiates from other interfaces.
	IsNonterminalContext()
}

type NonterminalContext struct {
	*antlr.BaseParserRuleContext
	parser  antlr.Parser
	nonterm *str.NonTerminal
	_NAME   antlr.Token
	r1      INonterm_ruleContext
	r2      INonterm_ruleContext
}

func NewEmptyNonterminalContext() *NonterminalContext {
	var p = new(NonterminalContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_nonterminal
	return p
}

func (*NonterminalContext) IsNonterminalContext() {}

func NewNonterminalContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *NonterminalContext {
	var p = new(NonterminalContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_nonterminal

	return p
}

func (s *NonterminalContext) GetParser() antlr.Parser { return s.parser }

func (s *NonterminalContext) Get_NAME() antlr.Token { return s._NAME }

func (s *NonterminalContext) Set_NAME(v antlr.Token) { s._NAME = v }

func (s *NonterminalContext) GetR1() INonterm_ruleContext { return s.r1 }

func (s *NonterminalContext) GetR2() INonterm_ruleContext { return s.r2 }

func (s *NonterminalContext) SetR1(v INonterm_ruleContext) { s.r1 = v }

func (s *NonterminalContext) SetR2(v INonterm_ruleContext) { s.r2 = v }

func (s *NonterminalContext) GetNonterm() *str.NonTerminal { return s.nonterm }

func (s *NonterminalContext) SetNonterm(v *str.NonTerminal) { s.nonterm = v }

func (s *NonterminalContext) NAME() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, 0)
}

func (s *NonterminalContext) AllNonterm_rule() []INonterm_ruleContext {
	var ts = s.GetTypedRuleContexts(reflect.TypeOf((*INonterm_ruleContext)(nil)).Elem())
	var tst = make([]INonterm_ruleContext, len(ts))

	for i, t := range ts {
		if t != nil {
			tst[i] = t.(INonterm_ruleContext)
		}
	}

	return tst
}

func (s *NonterminalContext) Nonterm_rule(i int) INonterm_ruleContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*INonterm_ruleContext)(nil)).Elem(), i)

	if t == nil {
		return nil
	}

	return t.(INonterm_ruleContext)
}

func (s *NonterminalContext) Nonterminal_params() INonterminal_paramsContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*INonterminal_paramsContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(INonterminal_paramsContext)
}

func (s *NonterminalContext) Nonterminal_returns() INonterminal_returnsContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*INonterminal_returnsContext)(nil)).Elem(), 0)

	if t == nil {
		return nil
	}

	return t.(INonterminal_returnsContext)
}

func (s *NonterminalContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *NonterminalContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *NonterminalContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterNonterminal(s)
	}
}

func (s *NonterminalContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitNonterminal(s)
	}
}

func (p *GospodGrammarParser) Nonterminal() (localctx INonterminalContext) {
	localctx = NewNonterminalContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 12, GospodGrammarParserRULE_nonterminal)

	localctx.(*NonterminalContext).nonterm = &str.NonTerminal{
		First:  map[str.Terminal]struct{}{},
		Follow: map[str.Terminal]struct{}{},
	}

	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(61)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*NonterminalContext)._NAME = _m
	}
	localctx.(*NonterminalContext).nonterm.Name = (func() string {
		if localctx.(*NonterminalContext).Get_NAME() == nil {
			return ""
		} else {
			return localctx.(*NonterminalContext).Get_NAME().GetText()
		}
	}())
	p.SetState(67)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	if _la == GospodGrammarParserT__6 {
		{
			p.SetState(63)
			p.Match(GospodGrammarParserT__6)
		}
		{
			p.SetState(64)
			p.Nonterminal_params(localctx.(*NonterminalContext).nonterm)
		}
		{
			p.SetState(65)
			p.Match(GospodGrammarParserT__7)
		}

	}
	p.SetState(74)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	if _la == GospodGrammarParserT__8 {
		{
			p.SetState(69)
			p.Match(GospodGrammarParserT__8)
		}
		{
			p.SetState(70)
			p.Match(GospodGrammarParserT__6)
		}
		{
			p.SetState(71)
			p.Nonterminal_returns(localctx.(*NonterminalContext).nonterm)
		}
		{
			p.SetState(72)
			p.Match(GospodGrammarParserT__7)
		}

	}
	{
		p.SetState(76)
		p.Match(GospodGrammarParserT__3)
	}
	{
		p.SetState(77)

		var _x = p.Nonterm_rule()

		localctx.(*NonterminalContext).r1 = _x
	}
	localctx.(*NonterminalContext).nonterm.Rules = append(localctx.(*NonterminalContext).nonterm.Rules, *localctx.(*NonterminalContext).GetR1().GetR())
	p.SetState(88)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for _la == GospodGrammarParserT__9 {
		{
			p.SetState(79)
			p.Match(GospodGrammarParserT__9)
		}
		p.SetState(84)
		p.GetErrorHandler().Sync(p)

		switch p.GetTokenStream().LA(1) {
		case GospodGrammarParserNAME:
			{
				p.SetState(80)

				var _x = p.Nonterm_rule()

				localctx.(*NonterminalContext).r2 = _x
			}
			localctx.(*NonterminalContext).nonterm.Rules = append(localctx.(*NonterminalContext).nonterm.Rules, *localctx.(*NonterminalContext).GetR2().GetR())

		case GospodGrammarParserT__1, GospodGrammarParserT__9:
			localctx.(*NonterminalContext).nonterm.Rules = localctx.(*NonterminalContext).nonterm.Rules

		default:
			panic(antlr.NewNoViableAltException(p, nil, nil, nil, nil, nil))
		}

		p.SetState(90)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}
	{
		p.SetState(91)
		p.Match(GospodGrammarParserT__1)
	}

	return localctx
}

// INonterminal_paramsContext is an interface to support dynamic dispatch.
type INonterminal_paramsContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// GetTpe returns the tpe token.
	GetTpe() antlr.Token

	// GetName returns the name token.
	GetName() antlr.Token

	// GetType1 returns the type1 token.
	GetType1() antlr.Token

	// GetName1 returns the name1 token.
	GetName1() antlr.Token

	// SetTpe sets the tpe token.
	SetTpe(antlr.Token)

	// SetName sets the name token.
	SetName(antlr.Token)

	// SetType1 sets the type1 token.
	SetType1(antlr.Token)

	// SetName1 sets the name1 token.
	SetName1(antlr.Token)

	// GetNonterm returns the nonterm attribute.
	GetNonterm() *str.NonTerminal

	// SetNonterm sets the nonterm attribute.
	SetNonterm(*str.NonTerminal)

	// IsNonterminal_paramsContext differentiates from other interfaces.
	IsNonterminal_paramsContext()
}

type Nonterminal_paramsContext struct {
	*antlr.BaseParserRuleContext
	parser  antlr.Parser
	nonterm *str.NonTerminal
	tpe     antlr.Token
	name    antlr.Token
	type1   antlr.Token
	name1   antlr.Token
}

func NewEmptyNonterminal_paramsContext() *Nonterminal_paramsContext {
	var p = new(Nonterminal_paramsContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_nonterminal_params
	return p
}

func (*Nonterminal_paramsContext) IsNonterminal_paramsContext() {}

func NewNonterminal_paramsContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, nonterm *str.NonTerminal) *Nonterminal_paramsContext {
	var p = new(Nonterminal_paramsContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_nonterminal_params

	p.nonterm = nonterm

	return p
}

func (s *Nonterminal_paramsContext) GetParser() antlr.Parser { return s.parser }

func (s *Nonterminal_paramsContext) GetTpe() antlr.Token { return s.tpe }

func (s *Nonterminal_paramsContext) GetName() antlr.Token { return s.name }

func (s *Nonterminal_paramsContext) GetType1() antlr.Token { return s.type1 }

func (s *Nonterminal_paramsContext) GetName1() antlr.Token { return s.name1 }

func (s *Nonterminal_paramsContext) SetTpe(v antlr.Token) { s.tpe = v }

func (s *Nonterminal_paramsContext) SetName(v antlr.Token) { s.name = v }

func (s *Nonterminal_paramsContext) SetType1(v antlr.Token) { s.type1 = v }

func (s *Nonterminal_paramsContext) SetName1(v antlr.Token) { s.name1 = v }

func (s *Nonterminal_paramsContext) GetNonterm() *str.NonTerminal { return s.nonterm }

func (s *Nonterminal_paramsContext) SetNonterm(v *str.NonTerminal) { s.nonterm = v }

func (s *Nonterminal_paramsContext) AllNAME() []antlr.TerminalNode {
	return s.GetTokens(GospodGrammarParserNAME)
}

func (s *Nonterminal_paramsContext) NAME(i int) antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, i)
}

func (s *Nonterminal_paramsContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Nonterminal_paramsContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Nonterminal_paramsContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterNonterminal_params(s)
	}
}

func (s *Nonterminal_paramsContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitNonterminal_params(s)
	}
}

func (p *GospodGrammarParser) Nonterminal_params(nonterm *str.NonTerminal) (localctx INonterminal_paramsContext) {
	localctx = NewNonterminal_paramsContext(p, p.GetParserRuleContext(), p.GetState(), nonterm)
	p.EnterRule(localctx, 14, GospodGrammarParserRULE_nonterminal_params)
	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(93)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Nonterminal_paramsContext).tpe = _m
	}
	{
		p.SetState(94)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Nonterminal_paramsContext).name = _m
	}
	localctx.(*Nonterminal_paramsContext).nonterm.AddParam((func() string {
		if localctx.(*Nonterminal_paramsContext).GetTpe() == nil {
			return ""
		} else {
			return localctx.(*Nonterminal_paramsContext).GetTpe().GetText()
		}
	}()), (func() string {
		if localctx.(*Nonterminal_paramsContext).GetName() == nil {
			return ""
		} else {
			return localctx.(*Nonterminal_paramsContext).GetName().GetText()
		}
	}()))
	p.SetState(102)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for _la == GospodGrammarParserT__10 {
		{
			p.SetState(96)
			p.Match(GospodGrammarParserT__10)
		}
		{
			p.SetState(97)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Nonterminal_paramsContext).type1 = _m
		}
		{
			p.SetState(98)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Nonterminal_paramsContext).name1 = _m
		}
		localctx.(*Nonterminal_paramsContext).nonterm.AddParam((func() string {
			if localctx.(*Nonterminal_paramsContext).GetType1() == nil {
				return ""
			} else {
				return localctx.(*Nonterminal_paramsContext).GetType1().GetText()
			}
		}()), (func() string {
			if localctx.(*Nonterminal_paramsContext).GetName1() == nil {
				return ""
			} else {
				return localctx.(*Nonterminal_paramsContext).GetName1().GetText()
			}
		}()))

		p.SetState(104)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// INonterminal_returnsContext is an interface to support dynamic dispatch.
type INonterminal_returnsContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// GetTpe returns the tpe token.
	GetTpe() antlr.Token

	// GetName returns the name token.
	GetName() antlr.Token

	// GetType1 returns the type1 token.
	GetType1() antlr.Token

	// GetName1 returns the name1 token.
	GetName1() antlr.Token

	// SetTpe sets the tpe token.
	SetTpe(antlr.Token)

	// SetName sets the name token.
	SetName(antlr.Token)

	// SetType1 sets the type1 token.
	SetType1(antlr.Token)

	// SetName1 sets the name1 token.
	SetName1(antlr.Token)

	// GetNonterm returns the nonterm attribute.
	GetNonterm() *str.NonTerminal

	// SetNonterm sets the nonterm attribute.
	SetNonterm(*str.NonTerminal)

	// IsNonterminal_returnsContext differentiates from other interfaces.
	IsNonterminal_returnsContext()
}

type Nonterminal_returnsContext struct {
	*antlr.BaseParserRuleContext
	parser  antlr.Parser
	nonterm *str.NonTerminal
	tpe     antlr.Token
	name    antlr.Token
	type1   antlr.Token
	name1   antlr.Token
}

func NewEmptyNonterminal_returnsContext() *Nonterminal_returnsContext {
	var p = new(Nonterminal_returnsContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_nonterminal_returns
	return p
}

func (*Nonterminal_returnsContext) IsNonterminal_returnsContext() {}

func NewNonterminal_returnsContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int, nonterm *str.NonTerminal) *Nonterminal_returnsContext {
	var p = new(Nonterminal_returnsContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_nonterminal_returns

	p.nonterm = nonterm

	return p
}

func (s *Nonterminal_returnsContext) GetParser() antlr.Parser { return s.parser }

func (s *Nonterminal_returnsContext) GetTpe() antlr.Token { return s.tpe }

func (s *Nonterminal_returnsContext) GetName() antlr.Token { return s.name }

func (s *Nonterminal_returnsContext) GetType1() antlr.Token { return s.type1 }

func (s *Nonterminal_returnsContext) GetName1() antlr.Token { return s.name1 }

func (s *Nonterminal_returnsContext) SetTpe(v antlr.Token) { s.tpe = v }

func (s *Nonterminal_returnsContext) SetName(v antlr.Token) { s.name = v }

func (s *Nonterminal_returnsContext) SetType1(v antlr.Token) { s.type1 = v }

func (s *Nonterminal_returnsContext) SetName1(v antlr.Token) { s.name1 = v }

func (s *Nonterminal_returnsContext) GetNonterm() *str.NonTerminal { return s.nonterm }

func (s *Nonterminal_returnsContext) SetNonterm(v *str.NonTerminal) { s.nonterm = v }

func (s *Nonterminal_returnsContext) AllNAME() []antlr.TerminalNode {
	return s.GetTokens(GospodGrammarParserNAME)
}

func (s *Nonterminal_returnsContext) NAME(i int) antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, i)
}

func (s *Nonterminal_returnsContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Nonterminal_returnsContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Nonterminal_returnsContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterNonterminal_returns(s)
	}
}

func (s *Nonterminal_returnsContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitNonterminal_returns(s)
	}
}

func (p *GospodGrammarParser) Nonterminal_returns(nonterm *str.NonTerminal) (localctx INonterminal_returnsContext) {
	localctx = NewNonterminal_returnsContext(p, p.GetParserRuleContext(), p.GetState(), nonterm)
	p.EnterRule(localctx, 16, GospodGrammarParserRULE_nonterminal_returns)
	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(105)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Nonterminal_returnsContext).tpe = _m
	}
	{
		p.SetState(106)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Nonterminal_returnsContext).name = _m
	}
	localctx.(*Nonterminal_returnsContext).nonterm.AddRet((func() string {
		if localctx.(*Nonterminal_returnsContext).GetTpe() == nil {
			return ""
		} else {
			return localctx.(*Nonterminal_returnsContext).GetTpe().GetText()
		}
	}()), (func() string {
		if localctx.(*Nonterminal_returnsContext).GetName() == nil {
			return ""
		} else {
			return localctx.(*Nonterminal_returnsContext).GetName().GetText()
		}
	}()))
	p.SetState(114)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for _la == GospodGrammarParserT__10 {
		{
			p.SetState(108)
			p.Match(GospodGrammarParserT__10)
		}
		{
			p.SetState(109)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Nonterminal_returnsContext).type1 = _m
		}
		{
			p.SetState(110)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Nonterminal_returnsContext).name1 = _m
		}
		localctx.(*Nonterminal_returnsContext).nonterm.AddRet((func() string {
			if localctx.(*Nonterminal_returnsContext).GetType1() == nil {
				return ""
			} else {
				return localctx.(*Nonterminal_returnsContext).GetType1().GetText()
			}
		}()), (func() string {
			if localctx.(*Nonterminal_returnsContext).GetName1() == nil {
				return ""
			} else {
				return localctx.(*Nonterminal_returnsContext).GetName1().GetText()
			}
		}()))

		p.SetState(116)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// INonterm_ruleContext is an interface to support dynamic dispatch.
type INonterm_ruleContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_NAME returns the _NAME token.
	Get_NAME() antlr.Token

	// Set_NAME sets the _NAME token.
	Set_NAME(antlr.Token)

	// Get_rule_params returns the _rule_params rule contexts.
	Get_rule_params() IRule_paramsContext

	// Get_rule_code returns the _rule_code rule contexts.
	Get_rule_code() IRule_codeContext

	// Set_rule_params sets the _rule_params rule contexts.
	Set_rule_params(IRule_paramsContext)

	// Set_rule_code sets the _rule_code rule contexts.
	Set_rule_code(IRule_codeContext)

	// GetR returns the r attribute.
	GetR() *str.Rule

	// GetParams returns the params attribute.
	GetParams() string

	// GetCode returns the code attribute.
	GetCode() string

	// SetR sets the r attribute.
	SetR(*str.Rule)

	// SetParams sets the params attribute.
	SetParams(string)

	// SetCode sets the code attribute.
	SetCode(string)

	// IsNonterm_ruleContext differentiates from other interfaces.
	IsNonterm_ruleContext()
}

type Nonterm_ruleContext struct {
	*antlr.BaseParserRuleContext
	parser       antlr.Parser
	r            *str.Rule
	params       string
	code         string
	_NAME        antlr.Token
	_rule_params IRule_paramsContext
	_rule_code   IRule_codeContext
}

func NewEmptyNonterm_ruleContext() *Nonterm_ruleContext {
	var p = new(Nonterm_ruleContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_nonterm_rule
	return p
}

func (*Nonterm_ruleContext) IsNonterm_ruleContext() {}

func NewNonterm_ruleContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *Nonterm_ruleContext {
	var p = new(Nonterm_ruleContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_nonterm_rule

	return p
}

func (s *Nonterm_ruleContext) GetParser() antlr.Parser { return s.parser }

func (s *Nonterm_ruleContext) Get_NAME() antlr.Token { return s._NAME }

func (s *Nonterm_ruleContext) Set_NAME(v antlr.Token) { s._NAME = v }

func (s *Nonterm_ruleContext) Get_rule_params() IRule_paramsContext { return s._rule_params }

func (s *Nonterm_ruleContext) Get_rule_code() IRule_codeContext { return s._rule_code }

func (s *Nonterm_ruleContext) Set_rule_params(v IRule_paramsContext) { s._rule_params = v }

func (s *Nonterm_ruleContext) Set_rule_code(v IRule_codeContext) { s._rule_code = v }

func (s *Nonterm_ruleContext) GetR() *str.Rule { return s.r }

func (s *Nonterm_ruleContext) GetParams() string { return s.params }

func (s *Nonterm_ruleContext) GetCode() string { return s.code }

func (s *Nonterm_ruleContext) SetR(v *str.Rule) { s.r = v }

func (s *Nonterm_ruleContext) SetParams(v string) { s.params = v }

func (s *Nonterm_ruleContext) SetCode(v string) { s.code = v }

func (s *Nonterm_ruleContext) AllNAME() []antlr.TerminalNode {
	return s.GetTokens(GospodGrammarParserNAME)
}

func (s *Nonterm_ruleContext) NAME(i int) antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, i)
}

func (s *Nonterm_ruleContext) AllRule_params() []IRule_paramsContext {
	var ts = s.GetTypedRuleContexts(reflect.TypeOf((*IRule_paramsContext)(nil)).Elem())
	var tst = make([]IRule_paramsContext, len(ts))

	for i, t := range ts {
		if t != nil {
			tst[i] = t.(IRule_paramsContext)
		}
	}

	return tst
}

func (s *Nonterm_ruleContext) Rule_params(i int) IRule_paramsContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*IRule_paramsContext)(nil)).Elem(), i)

	if t == nil {
		return nil
	}

	return t.(IRule_paramsContext)
}

func (s *Nonterm_ruleContext) AllRule_code() []IRule_codeContext {
	var ts = s.GetTypedRuleContexts(reflect.TypeOf((*IRule_codeContext)(nil)).Elem())
	var tst = make([]IRule_codeContext, len(ts))

	for i, t := range ts {
		if t != nil {
			tst[i] = t.(IRule_codeContext)
		}
	}

	return tst
}

func (s *Nonterm_ruleContext) Rule_code(i int) IRule_codeContext {
	var t = s.GetTypedRuleContext(reflect.TypeOf((*IRule_codeContext)(nil)).Elem(), i)

	if t == nil {
		return nil
	}

	return t.(IRule_codeContext)
}

func (s *Nonterm_ruleContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Nonterm_ruleContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Nonterm_ruleContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterNonterm_rule(s)
	}
}

func (s *Nonterm_ruleContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitNonterm_rule(s)
	}
}

func (p *GospodGrammarParser) Nonterm_rule() (localctx INonterm_ruleContext) {
	localctx = NewNonterm_ruleContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 18, GospodGrammarParserRULE_nonterm_rule)

	localctx.(*Nonterm_ruleContext).SetR(&str.Rule{})
	localctx.(*Nonterm_ruleContext).SetParams("")
	localctx.(*Nonterm_ruleContext).SetCode("")

	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	p.SetState(131)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for ok := true; ok; ok = _la == GospodGrammarParserNAME {
		{
			p.SetState(117)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Nonterm_ruleContext)._NAME = _m
		}
		p.SetState(123)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)

		if _la == GospodGrammarParserT__6 {
			{
				p.SetState(118)
				p.Match(GospodGrammarParserT__6)
			}
			{
				p.SetState(119)

				var _x = p.Rule_params()

				localctx.(*Nonterm_ruleContext)._rule_params = _x
			}
			localctx.(*Nonterm_ruleContext).params = localctx.(*Nonterm_ruleContext).Get_rule_params().GetS()
			{
				p.SetState(121)
				p.Match(GospodGrammarParserT__7)
			}

		}
		p.SetState(128)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)

		if _la == GospodGrammarParserSOURCE_CODE {
			{
				p.SetState(125)

				var _x = p.Rule_code()

				localctx.(*Nonterm_ruleContext)._rule_code = _x
			}
			localctx.(*Nonterm_ruleContext).code = localctx.(*Nonterm_ruleContext).Get_rule_code().GetS()

		}

		localctx.(*Nonterm_ruleContext).r.AddElement((func() string {
			if localctx.(*Nonterm_ruleContext).Get_NAME() == nil {
				return ""
			} else {
				return localctx.(*Nonterm_ruleContext).Get_NAME().GetText()
			}
		}()), localctx.(*Nonterm_ruleContext).params, localctx.(*Nonterm_ruleContext).code)
		localctx.(*Nonterm_ruleContext).SetParams("")
		localctx.(*Nonterm_ruleContext).SetCode("")

		p.SetState(133)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// IRule_paramsContext is an interface to support dynamic dispatch.
type IRule_paramsContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// GetN1 returns the n1 token.
	GetN1() antlr.Token

	// GetN2 returns the n2 token.
	GetN2() antlr.Token

	// SetN1 sets the n1 token.
	SetN1(antlr.Token)

	// SetN2 sets the n2 token.
	SetN2(antlr.Token)

	// GetS returns the s attribute.
	GetS() string

	// SetS sets the s attribute.
	SetS(string)

	// IsRule_paramsContext differentiates from other interfaces.
	IsRule_paramsContext()
}

type Rule_paramsContext struct {
	*antlr.BaseParserRuleContext
	parser antlr.Parser
	s      string
	n1     antlr.Token
	n2     antlr.Token
}

func NewEmptyRule_paramsContext() *Rule_paramsContext {
	var p = new(Rule_paramsContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_rule_params
	return p
}

func (*Rule_paramsContext) IsRule_paramsContext() {}

func NewRule_paramsContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *Rule_paramsContext {
	var p = new(Rule_paramsContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_rule_params

	return p
}

func (s *Rule_paramsContext) GetParser() antlr.Parser { return s.parser }

func (s *Rule_paramsContext) GetN1() antlr.Token { return s.n1 }

func (s *Rule_paramsContext) GetN2() antlr.Token { return s.n2 }

func (s *Rule_paramsContext) SetN1(v antlr.Token) { s.n1 = v }

func (s *Rule_paramsContext) SetN2(v antlr.Token) { s.n2 = v }

func (s *Rule_paramsContext) GetS() string { return s.s }

func (s *Rule_paramsContext) SetS(v string) { s.s = v }

func (s *Rule_paramsContext) AllNAME() []antlr.TerminalNode {
	return s.GetTokens(GospodGrammarParserNAME)
}

func (s *Rule_paramsContext) NAME(i int) antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserNAME, i)
}

func (s *Rule_paramsContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Rule_paramsContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Rule_paramsContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterRule_params(s)
	}
}

func (s *Rule_paramsContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitRule_params(s)
	}
}

func (p *GospodGrammarParser) Rule_params() (localctx IRule_paramsContext) {
	localctx = NewRule_paramsContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 20, GospodGrammarParserRULE_rule_params)
	localctx.(*Rule_paramsContext).SetS("")
	var _la int

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(135)

		var _m = p.Match(GospodGrammarParserNAME)

		localctx.(*Rule_paramsContext).n1 = _m
	}
	localctx.(*Rule_paramsContext).s += (func() string {
		if localctx.(*Rule_paramsContext).GetN1() == nil {
			return ""
		} else {
			return localctx.(*Rule_paramsContext).GetN1().GetText()
		}
	}())
	p.SetState(142)
	p.GetErrorHandler().Sync(p)
	_la = p.GetTokenStream().LA(1)

	for _la == GospodGrammarParserT__10 {
		{
			p.SetState(137)
			p.Match(GospodGrammarParserT__10)
		}
		{
			p.SetState(138)

			var _m = p.Match(GospodGrammarParserNAME)

			localctx.(*Rule_paramsContext).n2 = _m
		}
		localctx.(*Rule_paramsContext).s += ", " + (func() string {
			if localctx.(*Rule_paramsContext).GetN2() == nil {
				return ""
			} else {
				return localctx.(*Rule_paramsContext).GetN2().GetText()
			}
		}())

		p.SetState(144)
		p.GetErrorHandler().Sync(p)
		_la = p.GetTokenStream().LA(1)
	}

	return localctx
}

// IRule_codeContext is an interface to support dynamic dispatch.
type IRule_codeContext interface {
	antlr.ParserRuleContext

	// GetParser returns the parser.
	GetParser() antlr.Parser

	// Get_SOURCE_CODE returns the _SOURCE_CODE token.
	Get_SOURCE_CODE() antlr.Token

	// Set_SOURCE_CODE sets the _SOURCE_CODE token.
	Set_SOURCE_CODE(antlr.Token)

	// GetS returns the s attribute.
	GetS() string

	// SetS sets the s attribute.
	SetS(string)

	// IsRule_codeContext differentiates from other interfaces.
	IsRule_codeContext()
}

type Rule_codeContext struct {
	*antlr.BaseParserRuleContext
	parser       antlr.Parser
	s            string
	_SOURCE_CODE antlr.Token
}

func NewEmptyRule_codeContext() *Rule_codeContext {
	var p = new(Rule_codeContext)
	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(nil, -1)
	p.RuleIndex = GospodGrammarParserRULE_rule_code
	return p
}

func (*Rule_codeContext) IsRule_codeContext() {}

func NewRule_codeContext(parser antlr.Parser, parent antlr.ParserRuleContext, invokingState int) *Rule_codeContext {
	var p = new(Rule_codeContext)

	p.BaseParserRuleContext = antlr.NewBaseParserRuleContext(parent, invokingState)

	p.parser = parser
	p.RuleIndex = GospodGrammarParserRULE_rule_code

	return p
}

func (s *Rule_codeContext) GetParser() antlr.Parser { return s.parser }

func (s *Rule_codeContext) Get_SOURCE_CODE() antlr.Token { return s._SOURCE_CODE }

func (s *Rule_codeContext) Set_SOURCE_CODE(v antlr.Token) { s._SOURCE_CODE = v }

func (s *Rule_codeContext) GetS() string { return s.s }

func (s *Rule_codeContext) SetS(v string) { s.s = v }

func (s *Rule_codeContext) SOURCE_CODE() antlr.TerminalNode {
	return s.GetToken(GospodGrammarParserSOURCE_CODE, 0)
}

func (s *Rule_codeContext) GetRuleContext() antlr.RuleContext {
	return s
}

func (s *Rule_codeContext) ToStringTree(ruleNames []string, recog antlr.Recognizer) string {
	return antlr.TreesStringTree(s, ruleNames, recog)
}

func (s *Rule_codeContext) EnterRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.EnterRule_code(s)
	}
}

func (s *Rule_codeContext) ExitRule(listener antlr.ParseTreeListener) {
	if listenerT, ok := listener.(GospodGrammarListener); ok {
		listenerT.ExitRule_code(s)
	}
}

func (p *GospodGrammarParser) Rule_code() (localctx IRule_codeContext) {
	localctx = NewRule_codeContext(p, p.GetParserRuleContext(), p.GetState())
	p.EnterRule(localctx, 22, GospodGrammarParserRULE_rule_code)

	defer func() {
		p.ExitRule()
	}()

	defer func() {
		if err := recover(); err != nil {
			if v, ok := err.(antlr.RecognitionException); ok {
				localctx.SetException(v)
				p.GetErrorHandler().ReportError(p, v)
				p.GetErrorHandler().Recover(p, v)
			} else {
				panic(err)
			}
		}
	}()

	p.EnterOuterAlt(localctx, 1)
	{
		p.SetState(145)

		var _m = p.Match(GospodGrammarParserSOURCE_CODE)

		localctx.(*Rule_codeContext)._SOURCE_CODE = _m
	}

	localctx.(*Rule_codeContext).SetS((func() string {
		if localctx.(*Rule_codeContext).Get_SOURCE_CODE() == nil {
			return ""
		} else {
			return localctx.(*Rule_codeContext).Get_SOURCE_CODE().GetText()
		}
	}())[1 : len((func() string {
		if localctx.(*Rule_codeContext).Get_SOURCE_CODE() == nil {
			return ""
		} else {
			return localctx.(*Rule_codeContext).Get_SOURCE_CODE().GetText()
		}
	}()))-1])

	return localctx
}
