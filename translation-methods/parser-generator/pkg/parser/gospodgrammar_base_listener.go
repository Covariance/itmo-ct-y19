// Code generated from pkg/parser/GospodGrammar.g4 by ANTLR 4.9. DO NOT EDIT.

package parser // GospodGrammar

import "github.com/antlr/antlr4/runtime/Go/antlr"

// BaseGospodGrammarListener is a complete listener for a parse tree produced by GospodGrammarParser.
type BaseGospodGrammarListener struct{}

var _ GospodGrammarListener = &BaseGospodGrammarListener{}

// VisitTerminal is called when a terminal node is visited.
func (s *BaseGospodGrammarListener) VisitTerminal(node antlr.TerminalNode) {}

// VisitErrorNode is called when an error node is visited.
func (s *BaseGospodGrammarListener) VisitErrorNode(node antlr.ErrorNode) {}

// EnterEveryRule is called when any rule is entered.
func (s *BaseGospodGrammarListener) EnterEveryRule(ctx antlr.ParserRuleContext) {}

// ExitEveryRule is called when any rule is exited.
func (s *BaseGospodGrammarListener) ExitEveryRule(ctx antlr.ParserRuleContext) {}

// EnterGram is called when production gram is entered.
func (s *BaseGospodGrammarListener) EnterGram(ctx *GramContext) {}

// ExitGram is called when production gram is exited.
func (s *BaseGospodGrammarListener) ExitGram(ctx *GramContext) {}

// EnterHeader is called when production header is entered.
func (s *BaseGospodGrammarListener) EnterHeader(ctx *HeaderContext) {}

// ExitHeader is called when production header is exited.
func (s *BaseGospodGrammarListener) ExitHeader(ctx *HeaderContext) {}

// EnterTerminals is called when production terminals is entered.
func (s *BaseGospodGrammarListener) EnterTerminals(ctx *TerminalsContext) {}

// ExitTerminals is called when production terminals is exited.
func (s *BaseGospodGrammarListener) ExitTerminals(ctx *TerminalsContext) {}

// EnterTerminal_rule is called when production terminal_rule is entered.
func (s *BaseGospodGrammarListener) EnterTerminal_rule(ctx *Terminal_ruleContext) {}

// ExitTerminal_rule is called when production terminal_rule is exited.
func (s *BaseGospodGrammarListener) ExitTerminal_rule(ctx *Terminal_ruleContext) {}

// EnterStart_state is called when production start_state is entered.
func (s *BaseGospodGrammarListener) EnterStart_state(ctx *Start_stateContext) {}

// ExitStart_state is called when production start_state is exited.
func (s *BaseGospodGrammarListener) ExitStart_state(ctx *Start_stateContext) {}

// EnterNonterminals is called when production nonterminals is entered.
func (s *BaseGospodGrammarListener) EnterNonterminals(ctx *NonterminalsContext) {}

// ExitNonterminals is called when production nonterminals is exited.
func (s *BaseGospodGrammarListener) ExitNonterminals(ctx *NonterminalsContext) {}

// EnterNonterminal is called when production nonterminal is entered.
func (s *BaseGospodGrammarListener) EnterNonterminal(ctx *NonterminalContext) {}

// ExitNonterminal is called when production nonterminal is exited.
func (s *BaseGospodGrammarListener) ExitNonterminal(ctx *NonterminalContext) {}

// EnterNonterminal_params is called when production nonterminal_params is entered.
func (s *BaseGospodGrammarListener) EnterNonterminal_params(ctx *Nonterminal_paramsContext) {}

// ExitNonterminal_params is called when production nonterminal_params is exited.
func (s *BaseGospodGrammarListener) ExitNonterminal_params(ctx *Nonterminal_paramsContext) {}

// EnterNonterminal_returns is called when production nonterminal_returns is entered.
func (s *BaseGospodGrammarListener) EnterNonterminal_returns(ctx *Nonterminal_returnsContext) {}

// ExitNonterminal_returns is called when production nonterminal_returns is exited.
func (s *BaseGospodGrammarListener) ExitNonterminal_returns(ctx *Nonterminal_returnsContext) {}

// EnterNonterm_rule is called when production nonterm_rule is entered.
func (s *BaseGospodGrammarListener) EnterNonterm_rule(ctx *Nonterm_ruleContext) {}

// ExitNonterm_rule is called when production nonterm_rule is exited.
func (s *BaseGospodGrammarListener) ExitNonterm_rule(ctx *Nonterm_ruleContext) {}

// EnterRule_params is called when production rule_params is entered.
func (s *BaseGospodGrammarListener) EnterRule_params(ctx *Rule_paramsContext) {}

// ExitRule_params is called when production rule_params is exited.
func (s *BaseGospodGrammarListener) ExitRule_params(ctx *Rule_paramsContext) {}

// EnterRule_code is called when production rule_code is entered.
func (s *BaseGospodGrammarListener) EnterRule_code(ctx *Rule_codeContext) {}

// ExitRule_code is called when production rule_code is exited.
func (s *BaseGospodGrammarListener) ExitRule_code(ctx *Rule_codeContext) {}
