//
// Created by covariance on 03.05.2020.
//

#include <bits/stdc++.h>

int l;

class DKA {
private:
    int n;
    std::vector<bool> terminal;
    std::vector<std::unordered_map<char, int>> edges;

    bool _inverse_calculated;
    std::vector<std::vector<int>> _inverse;

    void _calculate_inverse() {
        if (_inverse_calculated) {
            return;
        }
        _inverse = std::vector<std::vector<int>>(n, std::vector<int>());
        for (int i = 0; i < n; i++) {
            for (auto edge : edges[i]) {
                _inverse[edge.second].push_back(i);
            }
        }
        _inverse_calculated = true;
    }

    bool _significant_calculated;
    std::vector<bool> _significant;

    void _significance_dfs_terminal(int v) {
        _significant[v] = true;
        for (int son : _inverse[v]) {
            if (!_significant[son]) {
                _significance_dfs_terminal(son);
            }
        }
    }

    void _significance_dfs_starting(std::vector<bool> *tmp, int v) {
        (*tmp)[v] = true;
        for (auto son : edges[v]) {
            if (!(*tmp)[son.second]) {
                _significance_dfs_starting(tmp, son.second);
            }
        }
    }

    void _calculate_significant() {
        if (_significant_calculated) {
            return;
        }
        _calculate_inverse();
        _significant = std::vector<bool>(n, false);
        for (int i = 0; i < n; i++) {
            if (terminal[i]) {
                _significance_dfs_terminal(i);
            }
        }
        std::vector<bool> tmp(n, false);
        _significance_dfs_starting(&tmp, 0);
        for (int i = 0; i < n; i++) {
            _significant[i] = _significant[i] & tmp[i];
        }
        _significant_calculated = true;
    }

    bool _cyclic_calculated;
    bool _cyclic;

    bool _cyclic_dfs(std::vector<int> *state, int v) {
        (*state)[v] = 1;
        for (auto son : edges[v]) {
            if (_significant[son.second]) {
                if ((*state)[son.second] == 1) {
                    return true;
                }
                if ((*state)[son.second] == 0 && _cyclic_dfs(state, son.second)) {
                    return true;
                }
            }
        }
        (*state)[v] = 2;
        return false;
    }

    void _calculate_cyclic() {
        if (_cyclic_calculated) {
            return;
        }
        _calculate_significant();
        std::vector<int> state(n, 0);
        _cyclic = _cyclic_dfs(&state, 0);
        _cyclic_calculated = true;
    }

    void _word_count(std::vector<int> *val, int v, int mod) {
        long long sum = 0;
        for (int son : _inverse[v]) {
            if (_significant[son]) {
                if ((*val)[son] == 0) {
                    _word_count(val, son, mod);
                }
                sum = (sum + (*val)[son]) % mod;
            }
        }
        (*val)[v] = (int) sum;
    }

public:
    DKA()
            : n(),
              terminal(),
              edges(),
              _significant_calculated(false),
              _cyclic_calculated(false),
              _cyclic(false),
              _inverse_calculated(false) {}

    DKA(int n, const std::vector<int> &terminalSet, const std::vector<std::pair<char, std::pair<int, int>>> &edgeset)
            : n(n),
              terminal(n, false),
              edges(n, std::unordered_map<char, int>()),
              _significant_calculated(false),
              _cyclic_calculated(false),
              _cyclic(false),
              _inverse_calculated(false) {
        for (int term : terminalSet) {
            terminal[term - 1] = true;
        }
        for (auto edge : edgeset) {
            edges[edge.second.first - 1].insert({edge.first, edge.second.second - 1});
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const DKA &dka) {
        for (int i = 0; i < dka.n; i++) {
            if (dka.terminal[i]) {
                out << "(" << i + 1 << "):";
            } else {
                out << i + 1 << ":";
            }
            for (auto edge : dka.edges[i]) {
                out << " [" << edge.first << "; " << edge.second + 1 << "]";
            }
            out << "\n";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, DKA &dka) {
        int m = 0, k = 0;
        in >> dka.n >> m >> k;
        dka.terminal.clear();
        dka.terminal.resize(dka.n, false);
        for (int i = 0; i < k; i++) {
            int tmp = 0;
            in >> tmp;
            dka.terminal[tmp - 1] = true;
        }
        dka.edges.clear();
        dka.edges.resize(dka.n, std::unordered_map<char, int>());
        for (int i = 0; i < m; i++) {
            int from = 0, to = 0;
            char ch;
            in >> from >> to >> ch;
            dka.edges[from - 1].insert({ch, to - 1});
        }
        return in;
    }

    bool accepts(const std::string &s) {
        int cur_vert = 0;
        std::unordered_map<char, int>::const_iterator got;
        for (char ch : s) {
            got = this->edges[cur_vert].find(ch);
            if (got == this->edges[cur_vert].end()) {
                return false;
            }
            cur_vert = this->edges[cur_vert].find(ch)->second;
        }
        return this->terminal[cur_vert];
    }

    int word_count(int mod) {
        _calculate_cyclic();
        if (_cyclic) return -1;
        std::vector<int> val(n, 0);
        val[0] = 1;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (terminal[i]) {
                _word_count(&val, i, mod);
                sum = (sum + val[i]) % mod;
            }
        }
        for (int i = 0; i < n; i++) {
            if (_significant[i]) {
                return (int) (sum % mod);
            }
        }
        return 0;
    }

    int word_count(int l, int mod) {
        std::vector<int> cur(n, 0), tmp;
        cur[0] = 1;
        for (int i = 0; i < l; i++) {
            tmp.clear();
            tmp.resize(n, 0);
            for (int j = 0; j < n; j++) {
                for (auto edge : edges[j]) {
                    tmp[edge.second] = (tmp[edge.second] + cur[j]) % mod;
                }
            }
            cur = tmp;
        }
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (terminal[i]) {
                sum += cur[i];
            }
        }
        return (int) (sum % mod);
    }
};

class NKA {
private:
    int n;
    std::vector<bool> terminal;
    std::vector<std::unordered_map<char, std::vector<int>>> edges;
public:
    NKA() : n(), terminal(), edges(0, std::unordered_map<char, std::vector<int>>()) {}

    friend std::ostream &operator<<(std::ostream &out, const NKA &nka) {
        for (int i = 0; i < nka.n; i++) {
            if (nka.terminal[i]) {
                out << "(" << i + 1 << "):";
            } else {
                out << i + 1 << ":";
            }
            for (const auto &edge : nka.edges[i]) {
                out << " [" << edge.first << ";";
                for (int to : edge.second) {
                    out << " " << to + 1;
                }
                out << "]";
            }
            out << "\n";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, NKA &nka) {
        int m, k;
        in >> nka.n >> m >> k >> l;
        nka.terminal.clear();
        nka.terminal.resize(nka.n, false);
        for (int i = 0; i < k; i++) {
            int tmp;
            in >> tmp;
            nka.terminal[tmp - 1] = true;
        }
        nka.edges.clear();
        nka.edges.resize(nka.n, std::unordered_map<char, std::vector<int>>());
        for (int i = 0; i < m; i++) {
            int from, to;
            char ch;
            in >> from >> to >> ch;
            nka.edges[from - 1][ch].push_back(to - 1);
        }
        return in;
    }

    bool accepts(const std::string &s) {
        std::set<int> cur;
        std::set<int> tmp;
        cur.insert(0);
        for (char c : s) {
            for (int vert : cur) {
                auto got = edges[vert].find(c);
                if (got != edges[vert].end()) {
                    for (int next : got->second) {
                        tmp.insert(next);
                    }
                }
            }
            cur = tmp;
            tmp.clear();
        }
        for (int term : cur) {
            if (terminal[term]) {
                return true;
            }
        }
        return false;
    }

    DKA thompson() {
        int cur_naming = 1;
        std::unordered_map<std::vector<bool>, int> lookup;
        std::queue<std::vector<bool>> q;

        std::set<char> alphabet;
        for (const auto &vert : edges) {
            for (const auto &edge : vert) {
                alphabet.insert(edge.first);
            }
        }

        std::vector<std::pair<char, std::pair<int, int>>> edgeset;
        std::vector<int> term_set;

        std::vector<bool> first(n, false);
        first[0] = true;
        if (terminal[0]) {
            term_set.push_back(1);
        }
        q.push(first);
        lookup.insert({first, 0});

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (char way : alphabet) {
                std::vector<bool> tmp(n, false);
                for (int i = 0; i < n; i++) {
                    if (cur[i]) {
                        if (edges[i].find(way) != edges[i].end()) {
                            for (int to : edges[i].find(way)->second) {
                                tmp[to] = true;
                            }
                        }
                    }
                }
                if (lookup.find(tmp) == lookup.end()) {
                    for (int i = 0; i < n; i++) {
                        if (tmp[i] && terminal[i]) {
                            term_set.push_back(cur_naming + 1);
                            break;
                        }
                    }
                    lookup.insert({tmp, cur_naming++});
                    q.push(tmp);
                }
                edgeset.push_back({way, {lookup.find(cur)->second + 1, lookup.find(tmp)->second + 1}});
            }
        }

        return DKA(cur_naming, term_set, edgeset);
    }
};

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
    NKA a;
    std::cin >> a;
    std::cout << a.thompson().word_count(l, 1000000000 + 7);
    return 0;
}