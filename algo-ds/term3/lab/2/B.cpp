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
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, start, finish;
  cin >> n >> start >> finish;
  --start;
  --finish;
  g.resize(n, vector<edge>());
  d.resize(n, -1);
  used.resize(n, false);

  int dist;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      cin >> dist;
      if (i != j && dist >= 0) {
        g[i].emplace_back(j, dist);
      }
    }
  }

  dijkstra(start);

  cout << d[finish];
}
