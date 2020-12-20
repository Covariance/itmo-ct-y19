//
// Created by covariance on 20.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int n, m, k;

vector<vector<int>> g, g_aux;
vector<int> match_r_to_l, match_l_to_r;
vector<bool> used;

bool kun(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int son : g[v]) {
    if (match_r_to_l[son] == -1 || kun(match_r_to_l[son])) {
      match_r_to_l[son] = v;
      match_l_to_r[v] = son;
      return true;
    }
  }
  return false;
}

vector<int> a;
vector<bool> l_used, r_used;

void dfs(int v, bool right) {
  if (right) {
    a.push_back(v + 1);
    r_used[v] = true;
    for (auto son : g_aux[v]) {
      if (!l_used[son] && match_l_to_r[son] != v) {
        dfs(son, false);
      }
    }
  } else {
    l_used[v] = true;
    if (match_l_to_r[v] != -1 && !r_used[match_l_to_r[v]]) {
      dfs(match_l_to_r[v], true);
    }
  }
}

void get_a() {
  g_aux.assign(m, vector<int>());
  for (int i = 0; i != n; ++i) {
    for (auto v : g[i]) {
      g_aux[v].push_back(i);
    }
  }

  a.clear();
  l_used.assign(n, false);
  r_used.assign(m, false);
  for (int i = 0; i != m; ++i) {
    if (match_r_to_l[i] == -1) {
      dfs(i, true);
      return;
    }
  }
}

int main() {
  while (cin >> n >> m >> k) {
    g.assign(n, vector<int>());
    match_r_to_l.assign(m, -1);
    match_l_to_r.assign(n, -1);

    for (int i = 0; i != k; ++i) {
      int left, right;
      cin >> left >> right;
      g[left - 1].push_back(right - 1);
    }

    bool flag = true;
    while (flag) {
      flag = false;
      used.assign(n, false);
      for (int i = 0; i != n; ++i) {
        if (match_l_to_r[i] == -1 && kun(i)) {
          flag = true;
        }
      }
    }

    if (find(match_r_to_l.begin(), match_r_to_l.end(), -1) == match_r_to_l.end()) {
      cout << 0 << endl << endl;
    } else {
      get_a();
      cout << a.size() << endl;
      sort(a.begin(), a.end());
      for (auto i : a) {
        cout << i << ' ';
      }
      cout << endl << endl;
    }
  }
  return 0;
}
