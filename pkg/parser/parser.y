%{
package parser

import (
	"log"
	"python-obfuscator/pkg/structure"
)

func setResult(lex yyLexer, result structure.Program) {
	lex.(*lexer).result = result
}
%}


%union{
	programComponentList []structure.ProgramComponent
	programComponent structure.ProgramComponent
	stringList []string
	functionBody struct {
		Body []structure.Line
                Return structure.Expr
        }
        exprList []structure.Expr
	str string
	line structure.Line
	hack interface{}
	expr structure.Expr
	entity structure.Entity
}

%start File

%type <programComponentList> Program
%type <programComponent> Function
%type <stringList> Args
%type <stringList> Tail
%type <functionBody> FunctionBody
%type <expr> Return
%type <entity> Line
%type <expr> FunctionCall
%type <exprList> ArgsExpr
%type <exprList> TailExpr
%type <line> Assignment
%type <expr> Expr

%token <str> NAME
%token ',' '(' ')' ':' '\'' '=' BREAK DEF RETURN TAB

%%
File : Program BREAK
		{
			log.Println("setting result of File")
			reverse($1)
			setResult(yylex, structure.Program{Content: $1})
		}
     | Program
		{
			log.Println("setting result of File")
			reverse($1)
			setResult(yylex, structure.Program{Content: $1})
		}

Program : Function BREAK Program
		{
			log.Println("appending Function to Program")
			$$ = append($3, $1)
		}
        | Line BREAK Program
        	{
        		log.Println("appending Line to Program")
        		$$ = append($3, $1)
        	}
        | /* empty rule */
        	{
        		log.Println("empty Program")
        		$$ = []structure.ProgramComponent{}
        	}

Function : DEF NAME '(' Args ')' ':' BREAK TAB FunctionBody
		{
			log.Println("parsing Function")
			reverse($4)
			reverse($9.Body)
			$$ = &structure.Function{
				Name: $2,
				Args: $4,
				Body: $9.Body,
				Return: $9.Return,
			}
		}

Args : NAME Tail
		{
			log.Println("parsing Args")
			$$ = append($2, $1)
		}
     | /* empty rule */
     		{
     			log.Println("empty Args")
     			$$ = []string{}
     		}

Tail : ',' NAME Tail
		{
			log.Println("parsing Tail")
			$$ = append($3, $2)
		}
     | /* empty rule */
     		{
     			log.Println("empty Tail")
     			$$ = []string{}
     		}

FunctionBody : Line BREAK TAB FunctionBody
		{
			$$ = struct {
                             	Body []structure.Line
                             	Return structure.Expr
                             }{Body: append($4.Body, $1), Return: $4.Return}
		}
             | Return
             	{
			$$ = struct {
                             	Body []structure.Line
                             	Return structure.Expr
                             }{Body: []structure.Line{}, Return: $1}
             	}
             | /* empty rule */
             	{
			$$ = struct {
                             	Body []structure.Line
                             	Return structure.Expr
                             }{Body: []structure.Line{}, Return: nil}
             	}

Return : RETURN Expr
		{
			$$ = $2
		}

Line : FunctionCall
		{
			log.Println("parsing FunctionCall into Line")
			$$ = $1
		}
     | Assignment
     		{
			log.Println("parsing Assignment into Line")
     			$$ = $1
     		}

FunctionCall : NAME '(' ArgsExpr ')'
		{
			log.Println("parsing FunctionCall")
			reverse($3)
			$$ = &structure.FunctionCall{Name: $1, Args: $3}
		}

ArgsExpr : Expr TailExpr
		{
			log.Println("parsing ArgsExpr")
			$$ = append($2, $1)
		}
         | /* empty rule */
         	{
         		log.Println("empty ArgsExpr")
         		$$ = []structure.Expr{}
         	}

TailExpr : ',' Expr TailExpr
		{
			log.Println("parsing TailExpr")
			$$ = append($3, $2)
		}
     	 | /* empty rule */
     		{
     			log.Println("empty TailExpr")
     			$$ = []structure.Expr{}
     		}

Assignment : NAME '=' Expr
		{
			log.Println("parsing Assignment")
			$$ = &structure.Assignment{Name: $1, Assignee: $3}
		}

Expr : FunctionCall
		{
			log.Println("parsing FunctionCall into Expr")
			$$ = $1
		}
     | '\'' NAME '\''
     		{
			log.Println("parsing Constant into Expr")
     			$$ = &structure.Constant{Content: $2}
     		}
     | NAME
     		{
			log.Println("parsing Name into Expr")
     			$$ = &structure.Name{Name: $1}
     		}

%%
