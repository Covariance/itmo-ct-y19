package structure

import (
	"strings"
)

type Entity interface {
	String() string
}

type Program struct {
	Content []ProgramComponent
}

func (r *Program) String() string {
	var sb strings.Builder

	for _, entity := range r.Content {
		sb.WriteString(entity.String())
		sb.WriteString("\n")
	}

	return sb.String()
}

type ProgramComponent interface {
	Entity
}

type Function struct {
	Name   string
	Args   []string
	Body   []Line
	Return Expr
}

func (r *Function) String() string {
	var sb strings.Builder

	sb.WriteString("def ")
	sb.WriteString(r.Name)
	sb.WriteString("(")
	sb.WriteString(strings.Join(r.Args, ","))
	sb.WriteString("):\n")

	for _, line := range r.Body {
		sb.WriteString("\t")
		sb.WriteString(line.String())
		sb.WriteString("\n")
	}

	if r.Return != nil {
		sb.WriteString("\t")
		sb.WriteString("return ")
		sb.WriteString(r.Return.String())
	}

	return sb.String()
}

type Line interface {
	ProgramComponent
}

type FunctionCall struct {
	Name string
	Args []Expr
}

func (r *FunctionCall) String() string {
	var args []string

	for _, arg := range r.Args {
		args = append(args, arg.String())
	}

	return r.Name + "(" + strings.Join(args, ",") + ")"
}

type Assignment struct {
	Name     string
	Assignee Expr
}

func (r *Assignment) String() string {
	return r.Name + "=" + r.Assignee.String()
}

type Expr interface {
	Entity
}

type Constant struct {
	Content string
}

func (r *Constant) String() string {
	return "'" + r.Content + "'"
}

type Name struct {
	Name string
}

func (r *Name) String() string {
	return r.Name
}
