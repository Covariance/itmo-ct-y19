//
// Created by covariance on 17.12.2020.
//
#include <bits/stdc++.h>

using namespace std;

struct edge {
  int to, max, flow;

  edge(int to, int max, int flow) : to(to), max(max), flow(flow) {}
};

vector<edge> edge_list;
vector<vector<size_t>> g;
vector<uint32_t> p;
vector<int> tmp;

bool iter() {
  queue<int> q({0});
  tmp.assign(g.size(), -1);
  tmp[0] = 0;
  while (!q.empty() && *tmp.rbegin() == -1) {
    for (size_t i = 0; i != g[q.front()].size(); ++i) {
      edge &cur = edge_list[g[q.front()][i]];
      if (tmp[cur.to] == -1 && cur.flow < cur.max) {
        q.push(cur.to);
        tmp[cur.to] = tmp[q.front()] + 1;
      }
    }
    q.pop();
  }
  return *tmp.rbegin() != -1;
}

int dfs(uint32_t v, int flow) {
  if (flow == 0 || v + 1 == g.size()) {
    return flow;
  }
  for (int pushed; p[v] != g[v].size(); ++p[v]) {
    edge &cur = edge_list[g[v][p[v]]];
    if (tmp[cur.to] == tmp[v] + 1 && (pushed = dfs(cur.to, min(flow, cur.max - cur.flow))) != 0) {
      cur.flow += pushed;
      edge_list[g[v][p[v]] ^ 1u].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

int main() {
  int n, m, from, to, flow;
  cin >> n >> m;

  g.assign(n, vector<size_t>());
  p.assign(n, 0);

  for (int i = 0; i != m; ++i) {
    cin >> from >> to >> flow;
    --from, --to;
    g[from].emplace_back(edge_list.size());
    edge_list.emplace_back(to, flow, 0);
    g[to].emplace_back(edge_list.size());
    edge_list.emplace_back(from, 0, 0);
  }

  int max_flow = 0;

  while (iter()) {
    while ((flow = dfs(0, 2e9)) != 0) {
      max_flow += flow;
    }
    fill(p.begin(), p.end(), 0);
  }

  cout << max_flow;

  return 0;
}
