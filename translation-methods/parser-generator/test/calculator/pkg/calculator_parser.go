// Code generated by GOSPOD parser generator. DO NOT EDIT.

package parser

import (
    "fmt"
    "strconv"
)

type calculatorParser struct {
	lexer calculatorLexer
}

func (r *calculatorParser) Parse() (Tree, error) {
	_, err := r.lexer.NextToken()
	if err != nil {
		return nil, fmt.Errorf("unable to get token from lexer: %w", err)
	}

	res, err := r.e()
	if err != nil {
		return nil, fmt.Errorf("unable to parse input: %w", err)
	}

	if r.lexer.Current().kind != END {
		return nil, fmt.Errorf("expecting end of input, got: %s", r.lexer.Current().kind.String())
	}

	return &res, nil
}


type factTree struct {
    BaseTree
    
    x int
    
}

type fTree struct {
    BaseTree
    
    x int
    
}

type t_Tree struct {
    BaseTree
    
    x int
    
}

type u_Tree struct {
    BaseTree
    
    x int
    
}

type eTree struct {
    BaseTree
    
    x int
    
}

type e_Tree struct {
    BaseTree
    
    x int
    
}

type tTree struct {
    BaseTree
    
    x int
    
}

type fact_Tree struct {
    BaseTree
    
    x int
    
}

type plus_opTree struct {
    BaseTree
    
    x int
    
}

type mul_opTree struct {
    BaseTree
    
    x int
    
}

type div_opTree struct {
    BaseTree
    
    x int
    
}

type uTree struct {
    BaseTree
    
    x int
    
}

type fact_opTree struct {
    BaseTree
    
    x int
    
}

type minus_opTree struct {
    BaseTree
    
    x int
    
}



func (r *calculatorParser) fact(

) (factTree, error) {
    res := factTree{
        BaseTree: BaseTree{Node: "fact"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MINUS, LB, DIGIT:
            res0, err := r.f()
if err != nil {
	return factTree{}, fmt.Errorf("unable to parse f in fact: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res0))
 val := res0.x; res1, err := r.fact_(val)
if err != nil {
	return factTree{}, fmt.Errorf("unable to parse fact_ in fact: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 res.x = res1.x; 
        
        default:
            return factTree{}, fmt.Errorf("expected one of [ MINUS  LB  DIGIT ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) f(

) (fTree, error) {
    res := fTree{
        BaseTree: BaseTree{Node: "f"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MINUS:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "MINUS:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return fTree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.f()
if err != nil {
	return fTree{}, fmt.Errorf("unable to parse f in f: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 res.x = -res1.x; 
        
        case LB:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "LB:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return fTree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.e()
if err != nil {
	return fTree{}, fmt.Errorf("unable to parse e in f: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "RB:" + token.value}))
 res.x = res1.x; _, err2 := r.lexer.NextToken()
if err2!= nil {
	return fTree{}, fmt.Errorf("unable to get token from lexer: %w", err2)
}

        
        case DIGIT:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "DIGIT:" + token.value}))
 res.x, _ = strconv.Atoi(token.GetValue()); _, err0 := r.lexer.NextToken()
if err0!= nil {
	return fTree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}

        
        default:
            return fTree{}, fmt.Errorf("expected one of [ MINUS LB DIGIT ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) e(

) (eTree, error) {
    res := eTree{
        BaseTree: BaseTree{Node: "e"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case LB, DIGIT, MINUS:
            res0, err := r.t()
if err != nil {
	return eTree{}, fmt.Errorf("unable to parse t in e: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res0))
 left := res0.x; res1, err := r.e_(left)
if err != nil {
	return eTree{}, fmt.Errorf("unable to parse e_ in e: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 res.x = res1.x; 
        
        default:
            return eTree{}, fmt.Errorf("expected one of [ LB  DIGIT  MINUS ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) e_(

    arg int,

) (e_Tree, error) {
    res := e_Tree{
        BaseTree: BaseTree{Node: "e_"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case PLUS:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "PLUS:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return e_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.t()
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse t in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 val := res1.x; res2, err := r.plus_op(arg, val)
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse plus_op in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))
 cur := res2.x; res3, err := r.e_(cur)
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse e_ in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res3))
 res.x = res3.x; 
        
        case MINUS:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "MINUS:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return e_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.t()
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse t in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 val := res1.x; res2, err := r.minus_op(arg, val)
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse minus_op in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))
 cur := res2.x; res3, err := r.e_(cur)
if err != nil {
	return e_Tree{}, fmt.Errorf("unable to parse e_ in e_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res3))
 res.x = res3.x; 
        
        case END, RB:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = arg; 
        
        default:
            return e_Tree{}, fmt.Errorf("expected one of [ PLUS MINUS END  RB ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) t(

) (tTree, error) {
    res := tTree{
        BaseTree: BaseTree{Node: "t"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MINUS, LB, DIGIT:
            res0, err := r.u()
if err != nil {
	return tTree{}, fmt.Errorf("unable to parse u in t: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res0))
 left := res0.x; res1, err := r.t_(left)
if err != nil {
	return tTree{}, fmt.Errorf("unable to parse t_ in t: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 res.x = res1.x; 
        
        default:
            return tTree{}, fmt.Errorf("expected one of [ MINUS  LB  DIGIT ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) t_(

    arg int,

) (t_Tree, error) {
    res := t_Tree{
        BaseTree: BaseTree{Node: "t_"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MUL:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "MUL:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return t_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.u()
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse u in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 val := res1.x; res2, err := r.mul_op(arg, val)
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse mul_op in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))
 cur := res2.x; res3, err := r.t_(cur)
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse t_ in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res3))
 res.x = res3.x; 
        
        case DIV:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "DIV:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return t_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.u()
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse u in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 val := res1.x; res2, err := r.div_op(arg, val)
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse div_op in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))
 cur := res2.x; res3, err := r.t_(cur)
if err != nil {
	return t_Tree{}, fmt.Errorf("unable to parse t_ in t_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res3))
 res.x = res3.x; 
        
        case MINUS, PLUS, RB, END:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = arg 
        
        default:
            return t_Tree{}, fmt.Errorf("expected one of [ MUL DIV MINUS  PLUS  RB  END ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) u_(

) (u_Tree, error) {
    res := u_Tree{
        BaseTree: BaseTree{Node: "u_"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case POW:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "POW:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return u_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.fact()
if err != nil {
	return u_Tree{}, fmt.Errorf("unable to parse fact in u_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 fmt.Println(res1.x); cur := res1.x; res2, err := r.u_()
if err != nil {
	return u_Tree{}, fmt.Errorf("unable to parse u_ in u_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))

                fmt.Println(cur, res2.x)
                result__ := 1;
                for i_ := 0; i_ < res2.x; i_++ {
                    result__ *= cur
                }
                res.x = result__
        
        
        case RB, DIV, MINUS, MUL, PLUS, END:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = 1 
        
        default:
            return u_Tree{}, fmt.Errorf("expected one of [ POW RB  DIV  MINUS  MUL  PLUS  END ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) fact_(

    arg int,

) (fact_Tree, error) {
    res := fact_Tree{
        BaseTree: BaseTree{Node: "fact_"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case EXCL:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EXCL:" + token.value}))
_, err0 := r.lexer.NextToken()
if err0!= nil {
	return fact_Tree{}, fmt.Errorf("unable to get token from lexer: %w", err0)
}
res1, err := r.fact_op(arg)
if err != nil {
	return fact_Tree{}, fmt.Errorf("unable to parse fact_op in fact_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))
 val := res1.x; res2, err := r.fact_(val)
if err != nil {
	return fact_Tree{}, fmt.Errorf("unable to parse fact_ in fact_: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res2))
 res.x = res2.x; 
        
        case END, RB, POW, PLUS, DIV, MINUS, MUL:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = arg; 
        
        default:
            return fact_Tree{}, fmt.Errorf("expected one of [ EXCL END  RB  POW  PLUS  DIV  MINUS  MUL ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) plus_op(

    a int,

    b int,

) (plus_opTree, error) {
    res := plus_opTree{
        BaseTree: BaseTree{Node: "plus_op"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case END, RB, PLUS, MINUS:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = a + b; 
        
        default:
            return plus_opTree{}, fmt.Errorf("expected one of [ END  RB  PLUS  MINUS ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) u(

) (uTree, error) {
    res := uTree{
        BaseTree: BaseTree{Node: "u"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MINUS, LB, DIGIT:
            res0, err := r.fact()
if err != nil {
	return uTree{}, fmt.Errorf("unable to parse fact in u: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res0))
 left := res0.x; res1, err := r.u_()
if err != nil {
	return uTree{}, fmt.Errorf("unable to parse u_ in u: %w", err)
}
res.SetChildren(append(res.GetChildren(), &res1))

                    fmt.Println(left, res1.x)
                    result__ := 1;
                    for i_ := 0; i_ < res1.x; i_++ {
                        result__ *= left
                    }
                    res.x = result__
            
        
        default:
            return uTree{}, fmt.Errorf("expected one of [ MINUS  LB  DIGIT ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) fact_op(

    arg int,

) (fact_opTree, error) {
    res := fact_opTree{
        BaseTree: BaseTree{Node: "fact_op"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case EXCL, MUL, POW, PLUS, DIV, MINUS, END, RB:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))

        result_ := 1;
        for i_ := 2; i_ <= arg; i_++ {
            result_ *= i_;
        }
        res.x = result_;
    
        
        default:
            return fact_opTree{}, fmt.Errorf("expected one of [ EXCL  MUL  POW  PLUS  DIV  MINUS  END  RB ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) minus_op(

    a int,

    b int,

) (minus_opTree, error) {
    res := minus_opTree{
        BaseTree: BaseTree{Node: "minus_op"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case PLUS, MINUS, END, RB:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = a - b; 
        
        default:
            return minus_opTree{}, fmt.Errorf("expected one of [ PLUS  MINUS  END  RB ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) mul_op(

    a int,

    b int,

) (mul_opTree, error) {
    res := mul_opTree{
        BaseTree: BaseTree{Node: "mul_op"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case RB, END, PLUS, MUL, DIV, MINUS:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = a * b; 
        
        default:
            return mul_opTree{}, fmt.Errorf("expected one of [ RB  END  PLUS  MUL  DIV  MINUS ], got: %s", token.kind.String())
    }

    return res, nil
}

func (r *calculatorParser) div_op(

    a int,

    b int,

) (div_opTree, error) {
    res := div_opTree{
        BaseTree: BaseTree{Node: "div_op"},
    }

    token := r.lexer.Current()

    switch token.kind {
        
        case MINUS, PLUS, END, RB, MUL, DIV:
            res.SetChildren(append(res.GetChildren(), &BaseTree{Node: "EPS:" + token.value}))
 res.x = a / b; 
        
        default:
            return div_opTree{}, fmt.Errorf("expected one of [ MINUS  PLUS  END  RB  MUL  DIV ], got: %s", token.kind.String())
    }

    return res, nil
}

