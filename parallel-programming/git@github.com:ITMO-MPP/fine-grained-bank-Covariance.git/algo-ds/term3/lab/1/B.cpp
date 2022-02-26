//
// Created by covariance on 05.09.2020.
//
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, component;

void top_sort(int v) {
  if (used[v]) {
    return;
  }
  used[v] = true;
  for (int i : g[v]) {
    top_sort(i);
  }
  order.push_back(v);
}

void dfs(int v, int cmp) {
  used[v] = true;
  component[v] = cmp;
  for (int i : gr[v]) {
    if (!used[i]) {
      dfs(i, cmp);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  g.resize(n);
  gr.resize(n);
  for (int i = 0; i != m; ++i) {
    int from, to;
    cin >> from >> to;
    from--;
    to--;
    g[from].push_back(to);
    gr[to].push_back(from);
  }

  used.assign(n, false);
  for (int i = 0; i != n; ++i) {
    top_sort(i);
  }
  reverse(order.begin(), order.end());

  used.assign(n, false);
  component.resize(n);
  int cnt = 0;
  for (int v : order) {
    if (!used[v]) {
      cnt++;
      dfs(v, cnt);
    }
  }
  cout << cnt << endl;
  for (int cmp : component) {
    cout << cmp << ' ';
  }
}
