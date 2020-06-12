//
// Created by covariance on 05.06.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct ksg {
    unordered_map<size_t, unordered_map<char, vector<size_t>>> g;
    size_t start;

    ksg() : g(), start(0) {}

    bool accept(const string &s) {
        unordered_set<size_t> states{start};

        for (char sym : s) {
            unordered_set<size_t> new_states;
            for (size_t state : states)
                if (g.find(state) != g.end() && g[state].find(sym) != g[state].end())
                    for (size_t to : g[state][sym]) new_states.insert(to);

            states = new_states;
        }

        for (size_t fin : states) if (fin == 0) return true;
        return false;
    }

    friend istream &operator>>(istream &in, ksg &ksg) {
        size_t n, from, to;
        char tmp, by;
        string s;
        in >> n >> tmp;
        ksg.start = tmp - 'A' + 1;
        for (size_t i = 0; i < n; i++) {
            in >> s;
            from = s[0] - 'A' + 1;
            in >> s;
            in >> s;
            by = s[0];
            to = (s.length() > 1) ? (s[1] - 'A' + 1) : 0;
            ksg.g[from][by].push_back(to);
        }
        return in;
    }
};

int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
    ksg k;
    cin >> k;
    size_t q;
    cin >> q;
    for (size_t i = 0; i < q; i++) {
        string s;
        cin >> s;
        cout << (k.accept(s) ? "yes\n" : "no\n");
    }
    return 0;
}