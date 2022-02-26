//
// Created by covariance on 04.09.2020.
//
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<bool> winnable;

bool dfs(int i) {
  if (used[i]) {
    return winnable[i];
  }
  used[i] = true;
  for (int son : g[i]) {
    if (!dfs(son)) {
      return winnable[i] = true;
    }
  }
  return winnable[i] = false;
}

int main() {
  int n, m, s;
  cin >> n >> m >> s;
  g.resize(n);
  used.resize(n, false);
  winnable.resize(n);
  for (int i = 0; i != m; ++i) {
    int from, to;
    cin >> from >> to;
    g[from - 1].emplace_back(to - 1);
  }
  cout << (dfs(s - 1) ? "First" : "Second") << " player wins";
}
