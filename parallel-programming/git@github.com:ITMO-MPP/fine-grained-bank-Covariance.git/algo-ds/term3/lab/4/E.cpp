//
// Created by covariance on 18.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 500;

struct edge {
  uint32_t from, to;
  long long max, flow;

  edge(uint32_t from, uint32_t to, long long max, long long flow)
      : from(from), to(to), max(max), flow(flow) {}
};

uint32_t n, m, from, to;
long long flow;
vector<edge> edge_list;
vector<size_t> g[MAX_N];
uint32_t p[MAX_N];
int tmp[MAX_N];

bool iter(queue<int> &q) {
  q.push(0);
  for (uint32_t i = 0; i != n; ++i) {
    tmp[i] = -1;
  }
  tmp[0] = 0;
  while (!q.empty() && tmp[n - 1] == -1) {
    for (size_t i = 0; i != g[q.front()].size(); ++i) {
      edge &cur = edge_list[g[q.front()][i]];
      if (tmp[cur.to] == -1 && cur.flow < cur.max) {
        q.push(cur.to);
        tmp[cur.to] = tmp[q.front()] + 1;
      }
    }
    q.pop();
  }
  return tmp[n - 1] != -1;
}

long long dfs(uint32_t v, long long cur_flow) {
  if (cur_flow == 0 || v + 1 == n) {
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

bool flag = true;
vector<pair<long long, list<uint32_t>>> decomposition;

void find_component(int start) {
  vector<bool> used_v(n);
  list<uint32_t> que;
  uint32_t cur = start;

  while (!used_v[cur] && cur + 1 != n) {
    int next_edge = -1;
    for (uint32_t e : g[cur]) {
      if (edge_list[e].flow > 0) {
        next_edge = e;
        break;
      }
    }
    if (next_edge == -1) {
      break;
    }

    que.push_back(next_edge);
    used_v[cur] = true;
    cur = edge_list[next_edge].to;
  }

  if (used_v[cur]) {
    while (edge_list[que.front()].from != cur) {
      que.pop_front();
    }
  }
  long long min = edge_list[*min_element(que.begin(), que.end(),
              [](const int a, const int b) -> bool {
                return edge_list[a].flow < edge_list[b].flow;
              })].flow;

  for (uint32_t e : que) {
    edge_list[e].flow -= min;
  }
  if (!que.empty()) {
    decomposition.emplace_back(min, move(que));
  } else {
    flag = false;
  }
}

void find_decomposition() {
  while (flag) {
    find_component(0);
  }

  for (uint32_t i = 0; i != n; ++i) {
    flag = true;
    while (flag) {
      find_component(i);
    }
  }
}

int main() {
  cin >> n >> m;

  while (m--) {
    cin >> from >> to >> flow;
    --from, --to;
    g[from].emplace_back(edge_list.size());
    edge_list.emplace_back(from, to, flow, 0);
    g[to].emplace_back(edge_list.size());
    edge_list.emplace_back(to, from, 0, 0);
  }

  long long max_flow = 0;
  queue<int> q;
  while (iter(q)) {
    while ((flow = dfs(0, numeric_limits<long long>::max())) != 0) {
      max_flow += flow;
    }
    memset(p, 0, n * sizeof(p[0]));
    while (!q.empty()) {
      q.pop();
    }
  }

  if (max_flow == 0) {
    cout << 0 << endl;
    return 0;
  }

  vector<uint32_t> path;
  find_decomposition();

  cout << decomposition.size() << endl;
  for (auto &dec : decomposition) {
    cout << dec.first << ' ' << dec.second.size();
    for (auto e : dec.second) {
      cout << ' ' << (e >> 1u) + 1;
    }
    cout << endl;
  }

  return 0;
}
