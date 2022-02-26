//
// Created by covariance on 28.09.2020.
//
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF 1e9 + 1

typedef struct edge {
  int weight;
  int to;

  edge(int weight, int to)
    : weight(weight)
    , to(to) {}
} edge;

std::vector<std::vector<edge>> g, gr;
std::vector<int> color;
std::vector<int> sorting;
std::vector<int> dist;

void dfs(int v) {
  color[v] = BLACK;
  for (edge son : g[v]) {
    if (color[son.to] == WHITE) {
      dfs(son.to);
    }
  }
}

void dfs2(int v) {
  color[v] = GRAY;
  for (edge son : gr[v]) {
    if (color[son.to] == WHITE) {
      dfs2(son.to);
    }
  }
  color[v] = BLACK;
  sorting.push_back(v);
}

int main() {
  int n, m;
  std::cin >> n >> m;

  int from, to, from_, to_, weight_;
  std::cin >> from >> to;
  --to;
  --from;

  g.resize(n);
  gr.resize(n);

  color.assign(n, WHITE);

  dist.assign(n, INF);
  dist[from] = 0;

  while (m--) {
    std::cin >> from_ >> to_ >> weight_;
    --from_;
    --to_;
    g[from_].emplace_back(weight_, to_);
  }

  dfs(from);
  if (color[to] == WHITE) {
    std::cout << "Unreachable";
    return 0;
  }

  for (int i = 0; i != n; ++i) {
    if (color[i] == BLACK) {
      for (edge son : g[i]) {
        if (color[son.to] == BLACK) {
          gr[i].push_back(son);
        }
      }
    }
  }

  std::fill(color.begin(), color.end(), WHITE);
  dfs2(from);
  std::reverse(sorting.begin(), sorting.end());
  for (int v : sorting) {
    for (edge edge : gr[v]) {
      dist[edge.to] = std::min(dist[edge.to], dist[v] + edge.weight);
    }
  }

  std::cout << dist[to];
  return 0;
}
