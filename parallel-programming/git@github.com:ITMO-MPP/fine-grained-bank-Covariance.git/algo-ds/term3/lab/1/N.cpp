//
// Created by covariance on 02.10.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef struct flight {
  int cost;
  int to;

  flight(int cost, int to)
    : cost(cost)
    , to(to) {}
} flight;

vector<vector<flight>> g, gr;
vector<bool> used;
vector<int> sorted;

void push(int x) {
  sorted.push_back(x);
}

void nothing(int x) {
  x = x;
}

void dfs(int v, int fuel, const vector<vector<flight>> &graph, void (*f)(int)) {
  used[v] = true;
  for (flight flight : graph[v]) {
    if (!used[flight.to] && flight.cost <= fuel) {
      dfs(flight.to, fuel, graph, f);
    }
  }
  (*f)(v);
}

bool check(int fuel) {
  fill(used.begin(), used.end(), false);

  for (size_t i = 0; i != used.size(); ++i) {
    if (!used[i]) {
      dfs(i, fuel, g, push);
    }
  }

  reverse(sorted.begin(), sorted.end());
  fill(used.begin(), used.end(), false);
  bool one = false;
  for (int i : sorted) {
    if (!used[i]) {
      dfs(i, fuel, gr, nothing);
      if (one) {
        return false;
      } else {
        one = true;
      }
    }
  }
  return true;
}

int main() {
  int n, cost;
  cin >> n;

  g.resize(n);
  gr.resize(n);
  used.resize(n);

  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      cin >> cost;
      if (i != j) {
        g[i].emplace_back(cost, j);
        gr[j].emplace_back(cost, i);
      }
    }
  }

  int l = 0, r = 1e9 + 1;
  while (l + 2 < r) {
    int m = l + (r - l) / 2;
    (check(m) ? r : l) = m + 1;
  }
  if (check(l)) {
    cout << l;
  } else {
    cout << l + 1;
  }
  return 0;
}
