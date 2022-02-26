//
// Created by covariance on 22.10.2020.
//
#include <bits/stdc++.h>

#define INF ((long long) 5223372036854775807L)
#define fs first
#define sc second

using namespace std;

typedef struct edge {
  int from;
  int to;
  long long w;

  edge(int from, int to, long long w)
    : from(from)
    , to(to)
    , w(w) {}
} edge;

vector<edge> edges;
vector<unordered_set<int>> g;
vector<long long> d;
vector<bool> cyc_reach;

void dfs(int v) {
  if (cyc_reach[v]) {
    return;
  }
  cyc_reach[v] = true;
  for (int son : g[v]) {
    dfs(son);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, s;
  cin >> n >> m >> s;

  g.assign(n, unordered_set<int>());
  d.assign(n, INF);
  d[--s] = 0;
  cyc_reach.assign(n, false);

  for (int i = 0; i != m; ++i) {
    int from, to;
    long long w;
    cin >> from >> to >> w;
    edges.emplace_back(--from, --to, w);
    g[from].insert(to);
  }

  for (int i = 0; i != n; ++i) {
    for (edge edge : edges) {
      if ((d[edge.from] < INF && d[edge.to] > d[edge.from] + edge.w)
          || d[edge.to] == -INF || d[edge.from] == -INF) {
        if (d[edge.from] < -edge.w - INF) {
          dfs(edge.from);
          d[edge.to] = -INF;
        } else {
          d[edge.to] = d[edge.from] + edge.w;
        }
        if (i == n - 1) {
          dfs(edge.from);
        }
      }
      if (d[edge.to] == -INF && i == n - 1) {
        dfs(edge.from);
      }
    }
  }

  for (int i = 0; i != n; ++i) {
    if (cyc_reach[i]) {
      cout << "-\n";
      continue;
    }
    if (d[i] == INF) {
      cout << "*\n";
      continue;
    }
    cout << d[i] << "\n";
  }

  return 0;
}
