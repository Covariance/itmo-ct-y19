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
                out << " [" << edge.first << "; " << edge.second + 1 << "]";
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
        in >> nka.n >> m >> k;
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
};

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
    std::string s;
    NKA a;
    std::cin >> s >> a;
    std::cout << (a.accepts(s) ? "Accepts" : "Rejects");
    return 0;
}