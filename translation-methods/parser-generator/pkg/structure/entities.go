package structure

type Terminal struct {
	Name  string
	Regex string
}

func (r *Terminal) IsEps() bool {
	return r.Regex == "EPS"
}

type Rule struct {
	Elements []struct {
		Name   string
		Params string
		Code   string
	}
}

func (r *Rule) AddElement(name, params, code string) {
	r.Elements = append(r.Elements, struct {
		Name   string
		Params string
		Code   string
	}{Name: name, Params: params, Code: code})
}

type Param struct {
	Name string
	Type string
}

type NonTerminal struct {
	Name    string
	Rules   []Rule
	Params  []Param
	Returns []Param

	First  map[Terminal]struct{}
	Follow map[Terminal]struct{}
}

func (r *NonTerminal) AddParam(name, tpe string) {
	r.Params = append(r.Params, Param{
		Name: name,
		Type: tpe,
	})
}

func (r *NonTerminal) AddRet(name, tpe string) {
	r.Returns = append(r.Returns, Param{
		Name: name,
		Type: tpe,
	})
}
