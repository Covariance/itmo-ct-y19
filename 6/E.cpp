//
// Created by covariance on 04.12.2020.
//
#define deg first
#define ind second
#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, from, to;
  cin >> n;

  vector<unordered_set<int>> g(n, unordered_set<int>());
  vector<int> degs(n, 0);

  for (int i = 0; i + 1 != n; ++i) {
    cin >> from >> to;
    ++degs[--from];
    ++degs[--to];
    g[from].insert(to);
    g[to].insert(from);
  }

  set<pair<int, int>> ord;
  for (int i = 0; i != n; ++i) {
    ord.insert({degs[i], i});
  }

  vector<int> ans;
  while (ord.size() > 2) {
    pair<int, int> ejected = *ord.begin();
    int other_end = *g[ejected.ind].begin();
    ord.erase(ord.begin());
    ord.erase(ord.find({degs[other_end], other_end}));
    --degs[other_end];
    ord.insert({degs[other_end], other_end});
    g[other_end].erase(g[other_end].find(ejected.ind));
    ans.push_back(other_end);
  }

  for (int v : ans) {
    cout << v + 1 << ' ';
  }

  return 0;
}