//
// Created by covariance on 02.10.2020.
//

#include <bits/stdc++.h>

#define INF 1e9 + 1

using namespace std;

int cur, counter;
vector<vector<int>> g;
vector<bool> used;
vector<int> colors, tin, stock;

int dfs(int v, int p) {
  tin[v] = ++cur;
  used[v] = true;
  int min_tin = tin[v];
  stock.push_back(v);
  for (int son : g[v]) {
    if (son != p) {
      min_tin = min(min_tin, tin[son]);
      if (!used[son]) {
        size_t stack_size = stock.size();
        int t_son = dfs(son, v);
        min_tin = min(min_tin, t_son);

        while (t_son > tin[v] && stock.size() > stack_size) {
          colors[*stock.rbegin()] = counter;
          stock.pop_back();
        }
        if (t_son > tin[v]) {
          ++counter;
        }
      }
    }
  }
  return min_tin;
}

int main() {
  int n, m;
  cin >> n >> m;

  g.assign(n, vector<int>());
  colors.assign(n, 0);
  tin.assign(n, INF);
  used.assign(n, false);
  cur = 0;
  counter = 0;

  for (int i = 0; i != m; ++i) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (int i = 0; i != n; ++i) {
    if (!used[i]) {
      dfs(i, -1);

      for (int v : stock) {
        colors[v] = counter;
      }
      stock.clear();

      ++counter;
    }
  }

  cout << counter << '\n';
  for (int color : colors) {
    cout << color + 1 << ' ';
  }

  return 0;
}
