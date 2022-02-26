package main

import (
	"flag"
	"log"
	"os"

	"mt-2/pkg/parser"

	"github.com/goccy/go-graphviz"
	"github.com/goccy/go-graphviz/cgraph"
)

func main() {
	input := flag.String("input", "input.txt", "specify input path")
	output := flag.String("output", "output.png", "specify output path for graph picture")
	flag.Parse()

	contents, err := os.ReadFile(*input)
	if err != nil {
		log.Fatal(err)
	}

	tree, err := parser.Parse([]rune(string(contents)))
	if err != nil {
		log.Fatal(err)
	}

	core := graphviz.New()
	defer func(core *graphviz.Graphviz) {
		_ = core.Close()
	}(core)

	gr, err := tree.ToGraphviz(core)
	if err != nil {
		log.Print(err)
		return
	}
	defer func(gr *cgraph.Graph) {
		_ = gr.Close()
	}(gr)

	if err := core.RenderFilename(gr, graphviz.PNG, *output); err != nil {
		log.Print(err)
		return
	}
}
