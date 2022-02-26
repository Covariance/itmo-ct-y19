//
// Created by covariance on 03.05.2020.
//

#include <bits/stdc++.h>

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
        if (v == 0) return;
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
        for (int i = 0; i < n; i++) {
            if (_significant[i]) {
                for (auto edge : edges[i]) {
                    if (edge.second == i) {
                        return -1;
                    }
                }
            }
        }
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
};

int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
    DKA k;
    std::cin >> k;
    std::cout << k.word_count(1000000000 + 7);
    return 0;
}