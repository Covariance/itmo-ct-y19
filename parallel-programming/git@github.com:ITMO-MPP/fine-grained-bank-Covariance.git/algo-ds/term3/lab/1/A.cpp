//
// Created by covariance on 04.09.2020.
//
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

vector<vector<int>> g;
vector<int> used;
vector<int> result;

bool dfs(int i) {
  switch (used[i]) {
    case WHITE:
      used[i] = GRAY;
      for (int son : g[i]) {
        if (!dfs(son)) {
          return false;
        }
      }
      used[i] = BLACK;
      result.emplace_back(i + 1);
      return true;
    case BLACK:
      return true;
    default:
      return false;
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n);
  used.resize(n, WHITE);
  for (int i = 0; i != m; ++i) {
    int from, to;
    cin >> from >> to;
    g[from - 1].emplace_back(to - 1);
  }
  for (int i = 0; i != n; ++i) {
    if (!dfs(i)) {
      cout << -1;
      return 0;
    }
  }
  reverse(result.begin(), result.end());
  for (int i : result) {
    cout << i << ' ';
  }
}
