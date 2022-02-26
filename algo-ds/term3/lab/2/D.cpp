//
// Created by covariance on 17.10.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct edge {
  int to;
  int weight;

  edge(int to, int weight)
    : to(to)
    , weight(weight) {}
} edge;

vector<vector<edge>> g;
vector<long long> d;
vector<bool> used;

void dijkstra(int start) {
  set<pair<long long, int>> q;
  q.insert({0, start});
  d[start] = 0;

  while (!q.empty()) {
    auto[ignored, v] = *q.begin();
    ++ignored;
    --ignored;
    q.erase(q.begin());
    used[v] = true;
    for (edge son : g[v]) {
      if (!used[son.to] && (d[v] + son.weight < d[son.to] || d[son.to] == -1)) {
        if (d[son.to] != -1) {
          q.erase(q.find({d[son.to], son.to}));
        }
        d[son.to] = d[v] + son.weight;
        q.insert({d[son.to], son.to});
      }
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n, vector<edge>());
  d.resize(n, -1);
  used.resize(n, false);

  for (int i = 0; i != m; ++i) {
    int from, to, weight;
    cin >> from >> to >> weight;
    g[--from].emplace_back(--to, weight);
    g[to].emplace_back(from, weight);
  }

  dijkstra(0);

  for (auto res : d) {
    cout << res << ' ';
  }

  return 0;
}
