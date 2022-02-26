# GOSPOD
GOSPOD stands for GO Simplified Parser Obstructionless Development.

## Development
Регенерировать парсер:
```shell
antlr4 -Dlanguage=Go pkg/parser/GospodGrammar.g4
```

Сбилдить + потестить:
```shell
go build -o bin/gospod cmd/parser-generator/main.go
./bin/gospod --input test/calculator/calculator.gspd --output test/calculator/pkg
```
