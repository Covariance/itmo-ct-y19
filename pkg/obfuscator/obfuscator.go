package obfuscator

import (
	"fmt"
	"math/big"
	"math/rand"
	"python-obfuscator/pkg/structure"
	"reflect"
	"strings"
	"time"
)

type obfuscator struct {
	currentGen       *big.Int
	rng              *rand.Rand
	insertionPercent int
	nameMapping      map[string]string
	unusedMappings   map[string]struct{}
}

func NewObfuscator() *obfuscator {
	return &obfuscator{
		currentGen:       big.NewInt(42),
		insertionPercent: 25,
		rng:              rand.New(rand.NewSource(time.Now().Unix())),
		nameMapping: map[string]string{
			"input": "input",
			"print": "print",
		},
		unusedMappings: map[string]struct{}{},
	}
}

const ones = "I1l"
const zeros = "0Oo"

func (r *obfuscator) generateNewNames() {
	base := fmt.Sprintf("%b", r.currentGen)
	r.unusedMappings[base] = struct{}{}
	indices := make([]int, len(base))

	for i := range indices {
		indices[i] = 0
	}

	for {
		indices[0]++
		for i := 0; i != len(indices)-1; i++ {
			if indices[i] < 3 {
				break
			}
			indices[i+1]++
			indices[i] = 0
		}
		if indices[len(indices)-1] == 3 {
			break
		}

		var sb strings.Builder
		for i, ind := range indices {
			if base[i] == '0' {
				sb.WriteByte(zeros[ind])
			} else {
				sb.WriteByte(ones[ind])
			}
		}
		r.unusedMappings[sb.String()] = struct{}{}
	}
}

func (r *obfuscator) getName() string {
	if len(r.unusedMappings) == 0 {
		r.generateNewNames()
		r.currentGen.Add(r.currentGen, big.NewInt(1))
	}

	var result string
	for k := range r.unusedMappings {
		result = k
		break
	}

	delete(r.unusedMappings, result)
	return result
}

func (r *obfuscator) giveName(name string) string {
	if mapped, ok := r.nameMapping[name]; ok {
		return mapped
	}

	newName := r.getName()

	r.nameMapping[name] = newName

	return newName
}

func (r *obfuscator) chooseRandomName() string {
	pos := r.rng.Intn(len(r.nameMapping))
	for _, v := range r.nameMapping {
		if pos == 0 {
			return v
		}
		pos--
	}

	return "input"
}

func (r *obfuscator) obfuscateExpr(expr structure.Expr) structure.Expr {
	if call, ok := expr.(*structure.FunctionCall); ok {
		return r.obfuscateFunctionCall(call)
	}

	if name, ok := expr.(*structure.Name); ok {
		return &structure.Name{Name: r.giveName(name.Name)}
	}

	if cons, ok := expr.(*structure.Constant); ok {
		return &structure.Constant{Content: cons.Content}
	}

	panic("unexpected type in expr obfuscator")
}

func (r *obfuscator) obfuscateAssignment(ass *structure.Assignment) *structure.Assignment {
	newName := r.giveName(ass.Name)

	return &structure.Assignment{
		Name:     newName,
		Assignee: r.obfuscateExpr(ass.Assignee),
	}
}

func (r *obfuscator) obfuscateFunctionCall(call *structure.FunctionCall) *structure.FunctionCall {
	newName := r.giveName(call.Name)

	newArgs := make([]structure.Expr, len(call.Args))
	for i, expr := range call.Args {
		newArgs[i] = r.obfuscateExpr(expr)
	}

	return &structure.FunctionCall{
		Name: newName,
		Args: newArgs,
	}
}

func (r *obfuscator) obfuscateLine(line structure.Line) structure.Line {
	if assignment, ok := line.(*structure.Assignment); ok {
		return r.obfuscateAssignment(assignment)
	}

	if call, ok := line.(*structure.FunctionCall); ok {
		return r.obfuscateFunctionCall(call)
	}

	fmt.Println(reflect.TypeOf(line))
	panic("unexpected type in line obfuscator")
}

func (r *obfuscator) obfuscateFun(fun *structure.Function) *structure.Function {
	newName := r.giveName(fun.Name)

	newArgs := make([]string, len(fun.Args))
	for i, arg := range fun.Args {
		newArgs[i] = r.giveName(arg)
	}

	newBody := make([]structure.Line, len(fun.Body))
	for i, line := range fun.Body {
		newBody[i] = r.obfuscateLine(line)
	}

	newReturn := r.obfuscateExpr(fun.Return)

	return &structure.Function{
		Name:   newName,
		Args:   newArgs,
		Body:   newBody,
		Return: newReturn,
	}
}

func (r *obfuscator) generateInsertion() structure.Line {
	newVar := r.getName()

	newAssignee := &structure.Constant{Content: r.getName()}

	return &structure.Assignment{
		Name:     newVar,
		Assignee: newAssignee,
	}
}

func (r *obfuscator) insertedLine() (structure.Line, bool) {
	if r.rng.Intn(100) >= r.insertionPercent {
		return nil, false
	}

	return r.generateInsertion(), true
}

func (r *obfuscator) obfuscate(program *structure.Program) *structure.Program {
	var obfuscated []structure.ProgramComponent

	for _, component := range program.Content {
		if fun, ok := component.(*structure.Function); ok {
			obfuscated = append(obfuscated, r.obfuscateFun(fun))
		} else if line, ok := component.(structure.Line); ok {
			obfuscated = append(obfuscated, r.obfuscateLine(line))
		}

		if inserted, ok := r.insertedLine(); ok {
			obfuscated = append(obfuscated, inserted)
		}
	}

	return &structure.Program{Content: obfuscated}
}

func Obfuscate(program *structure.Program) *structure.Program {
	return NewObfuscator().obfuscate(program)
}
