package graph

import (
	"strconv"
	"testing"

	"github.com/goccy/go-graphviz"
	"github.com/goccy/go-graphviz/cgraph"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func checkTreeAndGraphIdentical(t *testing.T, tree *Tree, graph *cgraph.Graph, node *cgraph.Node) {
	t.Helper()
	assert.Equal(t, tree.Node, node.Get("label"))

	nextNode := graph.FirstEdge(node)

	for _, child := range tree.Children {
		checkTreeAndGraphIdentical(t, child, graph, nextNode.Node())
		nextNode = graph.NextEdge(nextNode, node)
	}
}

func TestTreeToGraphviz(t *testing.T) {
	bambooGen := func() *Tree {
		tree := &Tree{
			Node:     "last",
			Children: nil,
		}
		for i := 0; i != 100; i++ {
			next := Tree{
				Node:     strconv.Itoa(i),
				Children: []*Tree{tree},
			}

			tree = &next
		}

		return tree
	}

	hedgehogGen := func() *Tree {
		root := &Tree{
			Node:     "root",
			Children: []*Tree{},
		}

		for i := 0; i != 100; i++ {
			root.Children = append(root.Children, &Tree{
				Node:     strconv.Itoa(i),
				Children: nil,
			})
		}

		return root
	}

	emptyGen := func() *Tree {
		return &Tree{
			Node:     "only",
			Children: nil,
		}
	}

	sameNamesHedgehogGen := func() *Tree {
		root := &Tree{
			Node:     "root",
			Children: []*Tree{},
		}

		for i := 0; i != 100; i++ {
			root.Children = append(root.Children, &Tree{
				Node:     "spike",
				Children: nil,
			})
		}

		return root
	}

	cases := map[string]func() *Tree{
		"bamboo":     bambooGen,
		"hedgehog":   hedgehogGen,
		"empty":      emptyGen,
		"same_names": sameNamesHedgehogGen,
	}

	for name, gen := range cases {
		t.Run(name, func(t *testing.T) {
			// Assign
			core := graphviz.New()
			defer func(core *graphviz.Graphviz) {
				require.NoError(t, core.Close())
			}(core)

			tree := gen()

			// Act
			graph, err := tree.ToGraphviz(core)
			require.NoError(t, err)
			defer func(graph *cgraph.Graph) {
				require.NoError(t, graph.Close())
			}(graph)

			// Assert
			checkTreeAndGraphIdentical(t, tree, graph, graph.FirstNode())
		})
	}
}
