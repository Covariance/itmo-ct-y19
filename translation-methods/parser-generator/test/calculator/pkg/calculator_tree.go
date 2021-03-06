// Code generated by GOSPOD parser generator. DO NOT EDIT.

package parser

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/goccy/go-graphviz"
	"github.com/goccy/go-graphviz/cgraph"
)

type Tree interface {
	GetName() string
	GetChildren() []Tree
	SetChildren([]Tree)
	String() string
}

type BaseTree struct {
	Node     string
	Children []Tree
}

func (r *BaseTree) GetName() string {
	return r.Node
}

func (r *BaseTree) GetChildren() []Tree {
	return r.Children
}

func (r *BaseTree) SetChildren(new []Tree) {
	r.Children = new
}

func (r *BaseTree) stringWithTabs(tabs int) string {
	res := strings.Repeat("\t", tabs) + r.Node + "\n"
	for _, child := range r.Children {
		res += child.String()
	}
	return res
}

func (r *BaseTree) String() string {
	return r.stringWithTabs(0)
}

func Equals(this, that Tree) bool {
	if this.GetName() != that.GetName() || len(this.GetChildren()) != len(that.GetChildren()) {
		return false
	}
	for i := range this.GetChildren() {
		if !Equals(this.GetChildren()[i], that.GetChildren()[i]) {
			return false
		}
	}
	return true
}

func toGraphvizDfs(graph *cgraph.Graph, tree Tree, id uint64) (*cgraph.Node, uint64, error) {
	thisNode, err := graph.CreateNode(strconv.FormatUint(id, 16)) // nolint:gomnd
	thisNode = thisNode.SetLabel(tree.GetName())
	if err != nil {
		return nil, 0, fmt.Errorf("unable to create node %s: %w", tree.GetName(), err)
	}

	for _, child := range tree.GetChildren() {
		thatNode, newID, err := toGraphvizDfs(graph, child, id+1)
		if err != nil {
			return nil, 0, err
		}

		if _, err := graph.CreateEdge("", thisNode, thatNode); err != nil {
			return nil, 0, fmt.Errorf("unable to create edge between %s and %s: %w", tree.GetName(), child.GetName(), err)
		}

		id = newID
	}

	return thisNode, id, nil
}

func ToGraphviz(core *graphviz.Graphviz, tree Tree) (*cgraph.Graph, error) {
	graph, err := core.Graph(graphviz.StrictDirected)
	if err != nil {
		return nil, fmt.Errorf("unable to create graph: %w", err)
	}

	if _, _, err := toGraphvizDfs(graph, tree, 0); err != nil {
		return nil, err
	}

	return graph, nil
}
