package generators

import (
	"fmt"
	"os"
	"strings"
	"text/template"
)

func GenerateCode(name, path string, values map[string]interface{}) error {
	tmpl, err := template.New(name + ".tmpl").
		Funcs(template.FuncMap{"StringsJoin": strings.Join}).
		ParseFiles("templates/" + name + ".tmpl")
	if err != nil {
		return fmt.Errorf("unable to open %s template: %w", name, err)
	}

	file, err := os.OpenFile(path, os.O_WRONLY|os.O_CREATE, 0666)
	if err != nil {
		return fmt.Errorf("unable to open output %s file: %w", name, err)
	}
	defer func() {
		_ = file.Close()
	}()

	return tmpl.Execute(file, values)
}
