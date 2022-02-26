//
// Created by covariance on 04.12.2020.
//

#include <bits/stdc++.h>

#include <utility>

using namespace std;

class poly {
 public:
  vector<int> coefs;

  poly() : coefs(1, 0) {}

  poly(int n) : coefs(n + 1, 0) {
    coefs[n] = 1;
  }

  friend ostream &operator<<(ostream &out, const poly &p) {
    for (int i = p.coefs.size(); i != 0; --i) {
      out << p.coefs[i - 1] << ' ';
    }
    return out;
  }

  static poly sub(const poly &a, const poly &b) {
    poly ret;
    if (a.coefs.size() > b.coefs.size()) {
      ret.coefs = vector<int>(a.coefs);
      for (int i = 0; i != b.coefs.size(); ++i) {
        ret.coefs[i] -= b.coefs[i];
      }
    } else {
      ret.coefs = vector<int>(b.coefs);
      for (int i = 0; i != a.coefs.size(); ++i) {
        ret.coefs[i] = a.coefs[i] - b.coefs[i];
      }
      for (int i = a.coefs.size(); i != b.coefs.size(); ++i) {
        ret.coefs[i] = -ret.coefs[i];
      }
    }
    return ret;
  }
};

class graph {
 public:
  vector<unordered_set<int>> g;
  explicit graph(int n) : g(n) {}
  explicit graph(vector<unordered_set<int>> g) : g(std::move(g)) {}

  [[nodiscard]] graph contract(int u, int v) const {
    vector<unordered_set<int>> g_new(g.size() - 1, unordered_set<int>());

    vector<int> trans(g.size());

    for (int i = 0, write_to = 0; i != g.size(); ++i, ++write_to) {
      if (i == u || i == v) {
        trans[i] = g_new.size() - 1;
        --write_to;
        continue;
      }
      trans[i] = write_to;
    }

    for (int i = 0; i != g.size(); ++i) {
      for (int to : g[i]) {
        if ((to == u && i == v) || (to == v && i == u)) continue;
        g_new[trans[i]].insert(trans[to]);
        g_new[trans[to]].insert(trans[i]);
      }
    }

    return graph(g_new);
  }

  [[nodiscard]] graph remove(int u, int v) const {
    graph ret(this->g);
    ret.g[u].erase(ret.g[u].find(v));
    ret.g[v].erase(ret.g[v].find(u));
    return ret;
  }

  poly count_that() {
    for (int v = 0; v != g.size(); ++v) {
      if (!g[v].empty()) {
        return poly::sub(remove(v, *g[v].begin()).count_that(), contract(v, *g[v].begin()).count_that());
      }
    }

    return poly(g.size());
  }
};

int main() {
  int n, m, from, to;
  cin >> n >> m;
  vector<unordered_set<int>> g(n);

  for (int i = 0; i != m; ++i) {
    cin >> from >> to;
    g[--from].insert(--to);
    g[to].insert(from);
  }

  poly res = graph(g).count_that();

  cout << res.coefs.size() - 1 << '\n' << res;

  return 0;
}