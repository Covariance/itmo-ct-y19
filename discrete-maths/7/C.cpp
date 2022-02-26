//
// Created by covariance on 22.12.2020.
//

//
// Created by covariance on 26.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<uint32_t>> g;
vector<int> match;
vector<bool> used;

bool kun(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int son : g[v]) {
    if (match[son] == -1 || kun(match[son])) {
      match[son] = v;
      return true;
    }
  }
  return false;
}

int main() {
#ifndef DEBUG
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);
#endif
  uint32_t n;
  cin >> n;

  vector<pair<uint32_t, uint32_t>> vertices;
  vertices.reserve(n);
  g.assign(n, vector<uint32_t>());
  match.assign(n, -1);

  for (uint32_t i = 0, w; i != n; ++i) {
    cin >> w;
    vertices.emplace_back(w, i);
  }

  for (uint32_t from = 0, to, cnt; from != n; ++from) {
    cin >> cnt;
    while (cnt--) {
      cin >> to;
      g[from].emplace_back(to - 1);
    }
  }

  sort(vertices.begin(),
       vertices.end(),
       [](const pair<uint32_t, uint32_t> &lhs, const pair<uint32_t, uint32_t> &rhs) -> bool {
         return lhs.first > rhs.first;
       });

  for (auto v : vertices) {
    used.assign(n, false);
    kun(v.second);
  }

  vector<uint32_t> ans(n, -1);

  for (uint32_t i = 0; i != n; ++i) {
    if (match[i] != -1) {
      ans[match[i]] = i;
    }
  }

  for (auto i : ans) {
    cout << i + 1 << ' ';
  }
  return 0;
}

