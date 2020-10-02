//
// Created by covariance on 01.10.2020.
//
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, gr;
vector<bool> used, res;
vector<int> sorted, comp;

size_t no(size_t i) {
  return i ^ 1u;
}

void dfs1(int v) {
  used[v] = true;
  for (int son : g[v]) {
    if (!used[son]) {
      dfs1(son);
    }
  }
  sorted.push_back(v);
}

void dfs2(int v, int comp_cnt) {
  comp[v] = comp_cnt;
  for (int son : gr[v]) {
    if (comp[son] == -1) {
      dfs2(son, comp_cnt);
    }
  }
}

bool two_sat() {
  size_t n = g.size();
  used.assign(n, false);
  comp.assign(n, -1);
  sorted.clear();
  for (size_t i = 0; i != n; ++i) {
    if (!used[i]) {
      dfs1(i);
    }
  }

  int comp_cnt = 0;
  for (size_t i = 0; i != n; ++i) {
    if (comp[sorted[n - i - 1]] == -1) {
      dfs2(sorted[n - i - 1], comp_cnt++);
    }
  }

  for (size_t i = 0; i != n; ++i) {
    if (comp[i] == comp[no(i)]) {
      return false;
    }
  }

  res.clear();
  res.resize(n);

  for (size_t i = 0; i != n; ++i) {
    res[i] = comp[i] > comp[no(i)];
  }

  return true;
}

void add_edge(int from, int to) {
  g[from].push_back(to);
  gr[to].push_back(from);
}

int main() {
  int n, m;
  cin >> n >> m;
  g.assign(2 * n, vector<int>());
  gr.assign(2 * n, vector<int>());
  for (int i = 0; i != m; ++i) {
    int from, to;
    char type;
    cin >> from >> to >> type;
    --from;
    --to;
    if (type == 'T') {
      add_edge(2 * from, 2 * to);
      add_edge(2 * to, 2 * from);
      add_edge(2 * from + 1, 2 * to + 1);
      add_edge(2 * to + 1, 2 * from + 1);
    } else {
      add_edge(2 * from, 2 * to + 1);
      add_edge(2 * to, 2 * from + 1);
      add_edge(2 * from + 1, 2 * to);
      add_edge(2 * to + 1, 2 * from);
    }

    if (!two_sat()) {
      cout << i << endl;
      return 0;
    }
  }
  cout << m << endl;
  return 0;
}
