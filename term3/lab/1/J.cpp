//
// Created by covariance on 22.09.2020.
//
#include <bits/stdc++.h>

#define UNUSED 0
#define WHITE 1
#define BLACK 2

std::vector<std::unordered_set<int>> g;
std::vector<int> color;

bool dfs(int v, int p, int cur_color) {
  color[v] = cur_color;
  for (int son : g[v]) {
    if (son != p) {
      if (color[son] == UNUSED) {
        if (!dfs(son, v, cur_color == BLACK ? WHITE : BLACK)) {
          return false;
        }
      } else if (color[son] == cur_color) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;

  g.assign(n, std::unordered_set<int>());
  color.assign(n, UNUSED);

  while (m--) {
    int from, to;
    std::cin >> from >> to;
    if (--from != --to) {
      g[from].insert(to);
      g[to].insert(from);
    } else {
      std::cout << "NO\n";
      return 0;
    }
  }

  for (size_t i = 0; i != n; ++i) {
    if (color[i] == UNUSED) {
      if (!dfs(i, -1, WHITE)) {
        std::cout << "NO\n";
        return 0;
      }
    }
  }
  std::cout << "YES\n";
  return 0;
}

