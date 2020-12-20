//
// Created by covariance on 20.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct edge {
  uint32_t to, cost;

  edge(uint32_t to, uint32_t cost) : to(to), cost(cost) {}
};

vector<vector<edge>> graph;

bool kun(uint32_t v, vector<int> &matching, vector<bool> &used, uint32_t threshold) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (edge son : graph[v]) {
    if (son.cost >= threshold
        && (matching[son.to] == -1 || kun(matching[son.to], matching, used, threshold))) {
      matching[son.to] = v;
      return true;
    }
  }
  return false;
}

uint32_t matching_size(uint32_t threshold) {
  uint32_t n = graph.size();
  vector<int> matching(graph.size(), -1);
  vector<bool> used;
  for (uint32_t i = 0; i != n; ++i) {
    used.assign(n, false);
    kun(i, matching, used, threshold);
  }
  uint32_t ans = 0;
  for (int par : matching) {
    if (par != -1) {
      ++ans;
    }
  }
  return ans;
}

bool check(uint32_t threshold) {
  return matching_size(threshold) == graph.size();
}

int main() {
  uint32_t n, cost, r = 0;
  cin >> n;

  graph.assign(n, vector<edge>());

  for (uint32_t i = 0; i != n; ++i) {
    for (uint32_t j = 0; j != n; ++j) {
      cin >> cost;
      graph[i].emplace_back(j, cost);
      r = max(cost, r);
    }
  }

  ++r;
  uint32_t l = 0, m;
  while (r > l + 1) {
    m = l + ((r - l) >> 1u);
    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }

  cout << l;

  return 0;
}
