//
// Created by covariance on 04.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> color;



void dfs(int v, int k) {
  if (color[v] != 0) {
    return;
  }
  color[v] = -1;
  vector<bool> allowed(k, true);
  for (int son : g[v]) {
    dfs(son, k);
    if (color[son] > 0) {
      allowed[color[son] - 1] = false;
    }
  }
  for (int i = 0; i != k; ++i) {
    if (allowed[i]) {
      color[v] = i + 1;
      return;
    }
  }
  assert(false);
}

int main() {
  int n, m, from, to;
  cin >> n >> m;
  g.assign(n, vector<int>());
  color.assign(n, 0);
  for (int i = 0; i != m; ++i) {
    cin >> from >> to;
    g[--from].push_back(--to);
    g[to].push_back(from);
  }

  size_t k = 0;
  for (auto &row : g) {
    k = max(k, row.size());
  }

  if (k % 2 == 0) {
    ++k;
  }

  int start = 0;
  for (int i = 0; i != n; ++i) {
    if (g[i].size() < k) {
      start = i;
      break;
    }
  }

  dfs(start, k);

  cout << k << '\n';
  for (int col : color) {
    cout << col << '\n';
  }

  return 0;
}