package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"python-obfuscator/pkg/obfuscator"
	"python-obfuscator/pkg/parser"
)

func main() {
	input := flag.String("input", "input.txt", "specify input path")
	output := flag.String("output", "output.txt", "specify output path for obfuscated code")
	flag.Parse()

	contents, err := os.ReadFile(*input)
	if err != nil {
		log.Fatal(err)
	}

	parser.EnableDebug()
	res, err := parser.Parse(string(contents))

	if err != nil {
		fmt.Printf("Unable to parse input: %v", err)
		return
	}

	obfuscated := obfuscator.Obfuscate(&res)

	if err := os.WriteFile(*output, []byte(obfuscated.String()), 0666); err != nil {
		fmt.Printf("Unable to write result: %v", err)
	}
}
