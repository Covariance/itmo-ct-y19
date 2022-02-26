//
// Created by covariance on 30.09.2020.
//
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define fs first
#define sc second

using namespace std;

struct pair_hash {
  std::size_t operator()(const std::pair<int, int>& p) const {
    return p.first * p.first + 31 * p.second;
  }
};

int n, l, pos;
vector<int> euler;
vector<vector<int>> g;
unordered_set<pair<int, int>, pair_hash> edges;

void add_edge(int a, int b) {
  edges.insert({min(a, b), max(a, b)});
}

void finish_subtree(int v, int p) {
  add_edge(p, v);
  g[p].push_back(v);

  for (int son : g[v]) {
    if (son > v) {
      add_edge(p, son);
    }
    g[p].push_back(son);
  }
}

void build_tree(int v, int p) {
  while (pos++ < l) {
    int current = euler[pos - 1];
    if (current == p) {
      finish_subtree(v, p);
      return;
    }
    build_tree(current, v);
  }
}

int main() {
  cin >> n >> l;
  pos = 1;
  euler.resize(l);
  g.resize(n);
  for (int i = 0; i != l; ++i) {
    cin >> euler[i];
    --euler[i];
  }

  build_tree(euler[0], n + 1);

  cout << edges.size() << '\n';
  for (auto e : edges) {
    cout << e.fs + 1 << ' ' << e.sc + 1 << endl;
  }
  return 0;
}

