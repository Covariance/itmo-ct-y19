package structure

var END = Terminal{
	Name:  "END",
	Regex: "",
}

type Grammar struct {
	Name         string
	Terminals    map[string]Terminal
	NonTerminals map[string]NonTerminal

	Start string
	Eps   Terminal
}

func (r *Grammar) AddTerminal(name, rule string) {
	term := Terminal{
		Name:  name,
		Regex: rule,
	}
	r.Terminals[name] = term
}

func (r *Grammar) AddNonTerminal(nonTerm NonTerminal) {
	r.NonTerminals[nonTerm.Name] = nonTerm
}

func (r *Grammar) findEpsilon() {
	for _, v := range r.Terminals {
		if v.IsEps() {
			r.Eps = v
			break
		}
	}
}

func (r *Grammar) calcRuleFirst(rule Rule, index int) map[Terminal]struct{} {
	res := map[Terminal]struct{}{}
	els := rule.Elements

	el := els[index]
	if term, ok := r.Terminals[el.Name]; ok {
		res[term] = struct{}{}
	} else {
		nonTerm := r.NonTerminals[el.Name]

		for k := range nonTerm.First {
			res[k] = struct{}{}
		}

		if _, ok := res[r.Eps]; ok && index+1 < len(els) {
			delete(res, r.Eps)
			for k := range r.calcRuleFirst(rule, index+1) {
				res[k] = struct{}{}
			}
		}
	}
	return res
}

func (r *Grammar) findFirst() {
	changes := true
	for changes {
		changes = false
		for _, nonTerm := range r.NonTerminals {
			for _, rule := range nonTerm.Rules {
				sz := len(nonTerm.First)

				for k, v := range r.calcRuleFirst(rule, 0) {
					nonTerm.First[k] = v
				}

				if sz != len(nonTerm.First) {
					changes = true
				}
			}
		}
	}
}

func (r *Grammar) findFollow() {
	nonTerm_ := r.NonTerminals[r.Start]

	nonTerm_.Follow[END] = struct{}{}

	changes := true
	for changes {
		changes = false
		for _, nonTermA := range r.NonTerminals {
			for _, rule := range nonTermA.Rules {
				els := rule.Elements
				ruleSz := len(els)
				for i := 0; i < ruleSz; i++ {
					el := els[i]
					if nonTermB, ok := r.NonTerminals[el.Name]; ok {
						prevSz := len(nonTermB.Follow)

						if i != ruleSz-1 {
							restFirst := r.calcRuleFirst(rule, i+1)
							if _, ok := restFirst[r.Eps]; ok {
								delete(restFirst, r.Eps)
								for k := range nonTermA.Follow {
									restFirst[k] = struct{}{}
								}
							}
							for k := range restFirst {
								nonTermB.Follow[k] = struct{}{}
							}
						} else {
							for k := range nonTermA.Follow {
								nonTermB.Follow[k] = struct{}{}
							}
						}

						if prevSz != len(nonTermB.Follow) {
							changes = true
						}
					}
				}
			}
		}
	}
}

func (r *Grammar) Compile() {
	r.findEpsilon()
	r.findFirst()
	r.findFollow()
}

func (r *Grammar) First(nonTerm NonTerminal, rule Rule, index int) map[Terminal]struct{} {
	first := r.calcRuleFirst(rule, index)
	if _, ok := first[r.Eps]; ok {
		delete(first, r.Eps)
		for k := range nonTerm.Follow {
			first[k] = struct{}{}
		}
	}
	return first
}
