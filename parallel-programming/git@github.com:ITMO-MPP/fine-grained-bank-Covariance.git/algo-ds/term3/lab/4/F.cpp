//
// Created by covariance on 18.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 500;

struct edge {
  uint32_t from, to;
  long long max, flow;
  int original;

  edge(uint32_t from, uint32_t to, long long max, long long flow, int original)
      : from(from), to(to), max(max), flow(flow), original(original) {}
};

struct original_edge {
  uint32_t from, to;
  long long min_cap, max_cap;

  original_edge(uint32_t from, uint32_t to, long long min_cap, long long max_cap)
      : from(from), to(to), min_cap(min_cap), max_cap(max_cap) {}
};

uint32_t n, m, from, to, source, runoff;
long long flow;
vector<edge> edge_list;
vector<uint32_t> g[MAX_N];
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
  long long max_flow = 0;
  queue<int> q;
  memset(p, 0, n * sizeof(p[0]));
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

int original_n;
vector<original_edge> original_edge_list;

int main() {
  cin >> original_n >> m;
  edge_list.reserve(m);
  while (m--) {
    long long mn, mx;
    cin >> from >> to >> mn >> mx;
    --from, --to;
    g[from].emplace_back(edge_list.size());
    edge_list.emplace_back(from, to, mx - mn, 0,
                           static_cast<int>(original_edge_list.size()));
    g[to].emplace_back(edge_list.size());
    edge_list.emplace_back(to, from, 0, 0, -1);
    original_edge_list.emplace_back(from, to, mn, mx);
  }
  n = original_n + 2;
  source = n - 2, runoff = n - 1;
  for (auto e : original_edge_list) {
    g[source].emplace_back(edge_list.size());
    edge_list.emplace_back(source, e.to, e.min_cap, 0, -1);
    g[e.to].emplace_back(edge_list.size());
    edge_list.emplace_back(e.to, source, 0, 0, -1);

    g[e.from].emplace_back(edge_list.size());
    edge_list.emplace_back(e.from, runoff, e.min_cap, 0, -1);
    g[runoff].emplace_back(edge_list.size());
    edge_list.emplace_back(runoff, e.from, 0, 0, -1);
  }

  din();

  for (auto e : edge_list) {
    if (e.from == source && e.flow != e.max) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  vector<long long> ans(original_edge_list.size());
  for (auto e : edge_list) {
    if (e.original != -1) {
      ans[e.original] = e.flow + original_edge_list[e.original].min_cap;
    }
  }

  for (auto f : ans) {
    cout << f << endl;
  }
}
