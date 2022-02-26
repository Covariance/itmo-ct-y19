//
// Created by covariance on 28.09.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct edge {
  int index;
  int to;

  edge(int index, int to)
    : index(index)
    , to(to) {}
} edge;

int tick = 1;
vector<vector<edge>> g;
vector<bool> used;
vector<int> time_enter, time_out;
set<int> bridges;

void dfs(int v, int p) {
  used[v] = true;
  time_enter[v] = time_out[v] = tick++;

  for (edge edge : g[v]) {
    if (edge.to != p) {
      if (used[edge.to]) {
        time_out[v] = min(time_enter[edge.to], time_out[v]);
      } else {
        dfs(edge.to, v);
        time_out[v] = min(time_out[edge.to], time_out[v]);
        if (time_enter[v] < time_out[edge.to]) {
          bridges.insert(edge.index);
        }
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  g.resize(n);
  used.assign(n, false);
  time_enter.resize(n);
  time_out.resize(n);

  int a, b;
  for (int i = 0; i != m; ++i) {
    cin >> a >> b;
    --a;
    --b;
    g[a].emplace_back(i, b);
    g[b].emplace_back(i, a);
  }

  for (int i = 0; i != n; ++i) {
    if (!used[i]) {
      dfs(i, -1);
    }
  }

  cout << bridges.size() << "\n";
  for (int bridge : bridges) {
    cout << bridge + 1 << ' ';
  }
  return 0;
}
