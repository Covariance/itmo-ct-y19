//
// Created by covariance on 02.10.2020.
//
#include <bits/stdc++.h>

#define INF 1e9 + 1

using namespace std;

typedef struct edge {
  int to;
  int index;

  edge(int to, int index)
    : to(to)
    , index(index) {}
} edge;

int cur, counter;
vector<vector<edge>> g;
vector<bool> used, used_edge;
vector<int> colors, tin, stock;

int dfs(int v, int p) {
  tin[v] = ++cur;
  used[v] = true;
  int min_tin = tin[v];
  for (edge son : g[v]) {
    if (son.to != p) {
      min_tin = min(min_tin, tin[son.to]);
      size_t stack_size = stock.size();
      if (!used_edge[son.index]) {
        stock.push_back(son.index);
        used_edge[son.index] = true;
      }
      if (!used[son.to]) {
        int t_son = dfs(son.to, v);
        min_tin = min(min_tin, t_son);

        while (t_son >= tin[v] && stock.size() > stack_size) {
          colors[*stock.rbegin()] = counter;
          stock.pop_back();
        }
        if (t_son >= tin[v]) {
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

  g.assign(n, vector<edge>());
  colors.assign(m, 0);
  tin.assign(n, INF);
  used.assign(n, false);
  used_edge.assign(m, false);

  cur = 0;
  counter = 0;

  for (int i = 0; i != m; i++) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].emplace_back(to, i);
    g[to].emplace_back(from, i);
  }

  for (int i = 0; i != n; ++i) {
    if (!used[i]) {
      dfs(i, -1);

      for (int v : stock) {
        colors[v] = counter;
      }

      if (!stock.empty()) {
        ++counter;
      }

      stock.clear();
    }
  }

  cout << counter << "\n";
  for (int color : colors) {
    cout << color + 1 << " ";
  }

  return 0;
}
