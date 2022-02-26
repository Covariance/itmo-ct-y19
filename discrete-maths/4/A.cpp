//
// Created by covariance on 02.05.2020.
//
#include <bits/stdc++.h>

class DKA {
private:
    int n;
    std::vector<bool> terminal;
    std::vector<std::unordered_map<char, int>> edges;
public:
    DKA() : n(), terminal(), edges() {}

    DKA(int n, const std::vector<int> &terminalSet, const std::vector<std::pair<char, std::pair<int, int>>> &edgeset)
            : n(n), terminal(n, false), edges(n, std::unordered_map<char, int>()) {
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
                out << " [" << edge.second << "; " << edge.first + 1 << "]";
            }
            out << "\n";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, DKA &dka) {
        int m, k;
        in >> dka.n >> m >> k;
        dka.terminal.clear();
        dka.terminal.resize(dka.n, false);
        for (int i = 0; i < k; i++) {
            int tmp;
            in >> tmp;
            dka.terminal[tmp - 1] = true;
        }
        dka.edges.clear();
        dka.edges.resize(dka.n, std::unordered_map<char, int>());
        for (int i = 0; i < m; i++) {
            int from, to;
            char ch;
            in >> from >> to >> ch;
            dka.edges[from - 1].insert({ch, to - 1});
        }
        return in;
    }

    bool accepts(const std::string& s) {
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
};

int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
    std::string s;
    DKA a;
    std::cin >> s >> a;
    std::cout << (a.accepts(s) ? "Accepts" : "Rejects");
    return 0;
}