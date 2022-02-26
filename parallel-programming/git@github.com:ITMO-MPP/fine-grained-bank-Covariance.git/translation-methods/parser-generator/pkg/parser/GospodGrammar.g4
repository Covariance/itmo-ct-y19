grammar GospodGrammar;

// parser to parse a user-defined parser

@header {
import str "parser-generator/pkg/structure"
// Suppress unused import error
var _ = str.Rule{}
}

gram[*str.Grammar g] @init{$g = &str.Grammar{}}:
    header[g] terminals[g] start_state[g] nonterminals[g];

header[*str.Grammar g]:
    '@grammar' NAME {$g.Name = $NAME.text} ';';

terminals[*str.Grammar g] :
    '@terminals'
    (terminal_rule[g])*;


// : TODO skip-rule?
terminal_rule[*str.Grammar g]:
    NAME ':' REGEXP ';' {
        $g.AddTerminal($NAME.text, $REGEXP.text[1:len($REGEXP.text) - 1]);
    };

start_state[*str.Grammar g]:
    '@start' ':' NAME {$g.Start = $NAME.text} ';';

nonterminals[*str.Grammar g]:
    '@rules' (nonterminal {$g.AddNonTerminal(*$nonterminal.nonterm);})+;

nonterminal returns [*str.NonTerminal nonterm]
@init {
    $nonterm = &str.NonTerminal{
        First: map[str.Terminal]struct{}{},
        Follow: map[str.Terminal]struct{}{},
    }
}:
    NAME {$nonterm.Name = $NAME.text}
    ('[' nonterminal_params[$nonterm] ']')?
    ('returns' '[' nonterminal_returns[$nonterm] ']')?
    ':' r1=nonterm_rule {$nonterm.Rules = append($nonterm.Rules, *$r1.r)}
    ('|' ((r2=nonterm_rule {$nonterm.Rules = append($nonterm.Rules, *$r2.r)}) |
     ({$nonterm.Rules = $nonterm.Rules}))
     )* ';';

nonterminal_params[*str.NonTerminal nonterm]:
    tpe=NAME name=NAME {$nonterm.AddParam($tpe.text, $name.text);}
    (',' type1=NAME name1=NAME {$nonterm.AddParam($type1.text, $name1.text);})*;

nonterminal_returns[*str.NonTerminal nonterm]:
    tpe=NAME name=NAME {$nonterm.AddRet($tpe.text, $name.text);}
        (',' type1=NAME name1=NAME {$nonterm.AddRet($type1.text, $name1.text);})*;

nonterm_rule returns [*str.Rule r] locals [string params, string code]
@init {
    $r = &str.Rule{};
    $params = "";
    $code = "";
}:
    (NAME ('[' rule_params {$params = $rule_params.s}']')? (rule_code {$code = $rule_code.s})? {
        $r.AddElement($NAME.text, $params, $code);
        $params = "";
        $code = "";
    })+;

rule_params returns[string s] @init{ $s = ""; }:
    n1=NAME {$s += $n1.text} (',' n2=NAME {$s += ", " + $n2.text})*;

rule_code returns[string s]:
    SOURCE_CODE {
        $s = $SOURCE_CODE.text[1:len($SOURCE_CODE.text) - 1];
    };

SKIP_WHITESPACES: [ \n\r\t]+ -> skip;
INT: [0-9]+;
NAME: [a-zA-Z][a-zA-Z0-9_]*;

REGEXP: '"' (~('"'))* '"';
SOURCE_CODE: '#' (~('#'))+ '#';
