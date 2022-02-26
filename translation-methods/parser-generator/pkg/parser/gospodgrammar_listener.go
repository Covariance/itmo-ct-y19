// Code generated from pkg/parser/GospodGrammar.g4 by ANTLR 4.9. DO NOT EDIT.

package parser // GospodGrammar

import "github.com/antlr/antlr4/runtime/Go/antlr"

// GospodGrammarListener is a complete listener for a parse tree produced by GospodGrammarParser.
type GospodGrammarListener interface {
	antlr.ParseTreeListener

	// EnterGram is called when entering the gram production.
	EnterGram(c *GramContext)

	// EnterHeader is called when entering the header production.
	EnterHeader(c *HeaderContext)

	// EnterTerminals is called when entering the terminals production.
	EnterTerminals(c *TerminalsContext)

	// EnterTerminal_rule is called when entering the terminal_rule production.
	EnterTerminal_rule(c *Terminal_ruleContext)

	// EnterStart_state is called when entering the start_state production.
	EnterStart_state(c *Start_stateContext)

	// EnterNonterminals is called when entering the nonterminals production.
	EnterNonterminals(c *NonterminalsContext)

	// EnterNonterminal is called when entering the nonterminal production.
	EnterNonterminal(c *NonterminalContext)

	// EnterNonterminal_params is called when entering the nonterminal_params production.
	EnterNonterminal_params(c *Nonterminal_paramsContext)

	// EnterNonterminal_returns is called when entering the nonterminal_returns production.
	EnterNonterminal_returns(c *Nonterminal_returnsContext)

	// EnterNonterm_rule is called when entering the nonterm_rule production.
	EnterNonterm_rule(c *Nonterm_ruleContext)

	// EnterRule_params is called when entering the rule_params production.
	EnterRule_params(c *Rule_paramsContext)

	// EnterRule_code is called when entering the rule_code production.
	EnterRule_code(c *Rule_codeContext)

	// ExitGram is called when exiting the gram production.
	ExitGram(c *GramContext)

	// ExitHeader is called when exiting the header production.
	ExitHeader(c *HeaderContext)

	// ExitTerminals is called when exiting the terminals production.
	ExitTerminals(c *TerminalsContext)

	// ExitTerminal_rule is called when exiting the terminal_rule production.
	ExitTerminal_rule(c *Terminal_ruleContext)

	// ExitStart_state is called when exiting the start_state production.
	ExitStart_state(c *Start_stateContext)

	// ExitNonterminals is called when exiting the nonterminals production.
	ExitNonterminals(c *NonterminalsContext)

	// ExitNonterminal is called when exiting the nonterminal production.
	ExitNonterminal(c *NonterminalContext)

	// ExitNonterminal_params is called when exiting the nonterminal_params production.
	ExitNonterminal_params(c *Nonterminal_paramsContext)

	// ExitNonterminal_returns is called when exiting the nonterminal_returns production.
	ExitNonterminal_returns(c *Nonterminal_returnsContext)

	// ExitNonterm_rule is called when exiting the nonterm_rule production.
	ExitNonterm_rule(c *Nonterm_ruleContext)

	// ExitRule_params is called when exiting the rule_params production.
	ExitRule_params(c *Rule_paramsContext)

	// ExitRule_code is called when exiting the rule_code production.
	ExitRule_code(c *Rule_codeContext)
}
