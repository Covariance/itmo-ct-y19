package main

import (
	"flag"
	"log"
	"parser-generator/pkg/generators/lexer"
	"parser-generator/pkg/generators/parser"
	gspd "parser-generator/pkg/parser"
)

func main() {
	input := flag.String("input", "input.gspd", "Provide input file with grammar for GOSPOD")
	output := flag.String("output", "parser", "Provide output directory for GOSPOD-generated files")
	flag.Parse()

	gr, err := gspd.ParseGospodGrammar(*input)
	if err != nil {
		log.Fatal(err)
	}
	gr.Compile()

	if err := lexer.GenerateLexer(*gr, *output); err != nil {
		log.Fatal(err)
	}

	if err := parser.GenerateParser(*gr, *output); err != nil {
		log.Fatal(err)
	}
}
