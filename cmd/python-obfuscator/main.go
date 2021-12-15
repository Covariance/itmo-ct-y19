package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"python-obfuscator/pkg/obfuscator"
	"python-obfuscator/pkg/parser"
)

func launchObfuscator(input, output string, debug bool) error {
	contents, err := os.ReadFile(input)
	if err != nil {
		log.Fatal(err)
	}

	if debug {
		parser.EnableDebug()
	}

	res, err := parser.Parse(string(contents))
	if err != nil {
		return fmt.Errorf("unable to parse input: %w", err)
	}

	obfuscated := obfuscator.Obfuscate(&res)

	if err := os.WriteFile(output, []byte(obfuscated.String()), 0666); err != nil {
		return fmt.Errorf("unable to write result: %w", err)
	}

	return nil
}

func main() {
	input := flag.String("input", "input.txt", "specify input path")
	output := flag.String("output", "output.txt", "specify output path for obfuscated code")
	debug := flag.Bool("debug", false, "enable debug logging for parser")
	flag.Parse()

	if err := launchObfuscator(*input, *output, *debug); err != nil {
		log.Fatal(err)
	}
}
