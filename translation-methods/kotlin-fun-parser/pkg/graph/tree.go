package graph

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/goccy/go-graphviz"
	"github.com/goccy/go-graphviz/cgraph"
)

type Tree struct {
	Node     string
	Children []*Tree
}

func (r *Tree) Equals(other *Tree) bool {
	if r.Node != other.Node || len(r.Children) != len(other.Children) {
		return false
	}
	for i := range r.Children {
		if !r.Children[i].Equals(other.Children[i]) {
			return false
		}
	}
	return true
}

func (r *Tree) stringWithTabs(tabs int) string {
	res := strings.Repeat("\t", tabs) + r.Node + "\n"
	for _, child := range r.Children {
		res += child.stringWithTabs(tabs + 1)
	}
	return res
}

func (r *Tree) String() string {
	return r.stringWithTabs(0)
}

func (r *Tree) toGraphvizDfs(graph *cgraph.Graph, id uint64) (*cgraph.Node, uint64, error) {
	thisNode, err := graph.CreateNode(strconv.FormatUint(id, 16)) // nolint:gomnd
	thisNode = thisNode.SetLabel(r.Node)
	if err != nil {
		return nil, 0, fmt.Errorf("unable to create node %s: %w", r.Node, err)
	}

	for _, child := range r.Children {
		thatNode, newID, err := child.toGraphvizDfs(graph, id+1)
		if err != nil {
			return nil, 0, err
		}

		if _, err := graph.CreateEdge("", thisNode, thatNode); err != nil {
			return nil, 0, fmt.Errorf("unable to create edge between %s and %s: %w", r.Node, child.Node, err)
		}

		id = newID
	}

	return thisNode, id, nil
}

func (r *Tree) ToGraphviz(core *graphviz.Graphviz) (*cgraph.Graph, error) {
	graph, err := core.Graph(graphviz.StrictDirected)
	if err != nil {
		return nil, fmt.Errorf("unable to create graph: %w", err)
	}

	if _, _, err := r.toGraphvizDfs(graph, 0); err != nil {
		return nil, err
	}

	return graph, nil
}
