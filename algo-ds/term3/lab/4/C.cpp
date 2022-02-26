//
// Created by covariance on 20.12.2020.
//
#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 500;

struct edge {
  uint32_t to;
  long long max, flow;

  edge(uint32_t to, long long max, long long flow)
      : to(to), max(max), flow(flow) {}
};

uint32_t n, m, from, to, source, runoff;
long long flow;
vector<edge> edge_list;
vector<size_t> g[MAX_N];
uint32_t p[MAX_N];
int tmp[MAX_N];

bool iter(queue<int> &q) {
  q.push(source);
  for (uint32_t i = 0; i != n; ++i) {
    tmp[i] = -1;
  }
  tmp[source] = 0;
  while (!q.empty() && tmp[runoff] == -1) {
    for (size_t i = 0; i != g[q.front()].size(); ++i) {
      edge &cur = edge_list[g[q.front()][i]];
      if (tmp[cur.to] == -1 && cur.flow < cur.max) {
        q.push(cur.to);
        tmp[cur.to] = tmp[q.front()] + 1;
      }
    }
    q.pop();
  }
  return tmp[runoff] != -1;
}

long long dfs(uint32_t v, long long cur_flow) {
  if (cur_flow == 0 || v == runoff) {
    return cur_flow;
  }
  for (long long pushed; p[v] != g[v].size(); ++p[v]) {
    edge &cur = edge_list[g[v][p[v]]];
    if (tmp[cur.to] == tmp[v] + 1
        && (pushed = dfs(cur.to, min(cur_flow, cur.max - cur.flow))) != 0) {
      cur.flow += pushed;
      edge_list[g[v][p[v]] ^ 1u].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

long long din() {
  memset(p, 0, n * sizeof(p[0]));
  long long max_flow = 0;
  queue<int> q;
  while (iter(q)) {
    while ((flow = dfs(source, numeric_limits<long long>::max())) != 0) {
      max_flow += flow;
    }
    memset(p, 0, n * sizeof(p[0]));
    while (!q.empty()) {
      q.pop();
    }
  }
  return max_flow;
}

void dfs2(uint32_t v, vector<int> &used) {
  used[v] = 1;
  for (auto eid : g[v]) {
    if (!used[edge_list[eid].to] && edge_list[eid].max > edge_list[eid].flow) {
      dfs2(edge_list[eid].to, used);
    }
  }
}

int main() {
  cin >> n >> m;
  source = 0, runoff = n - 1;
  while (m--) {
    cin >> from >> to >> flow;
    --from, --to;
    g[from].emplace_back(edge_list.size());
    edge_list.emplace_back(to, flow, 0);
    g[to].emplace_back(edge_list.size());
    edge_list.emplace_back(from, 0, 0);

    g[to].emplace_back(edge_list.size());
    edge_list.emplace_back(from, flow, 0);
    g[from].emplace_back(edge_list.size());
    edge_list.emplace_back(to, 0, 0);
  }

  din();

  vector<int> used(n, 0);
  dfs2(source, used);
  cout << accumulate(used.begin(), used.end(), 0) << endl;
  for (uint32_t i = 0; i != used.size(); ++i) {
    if (used[i] == 1) {
      cout << i + 1 << ' ';
    }
  }
  return 0;
}
