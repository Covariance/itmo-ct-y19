//
// Created by covariance on 26.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

unordered_set<bitset<20>> dependent;

void bitmask_dfs(bitset<20> mask) {
  dependent.insert(mask);
  if (mask.count() != 20) {
    for (uint32_t i = 0; i != 20u; ++i) {
      if (!mask.test(i)) {
        mask.set(i);
        if (dependent.find(mask) == dependent.end()) {
          bitmask_dfs(mask);
        }
        mask.reset(i);
      }
    }
  }
}

int main() {
#ifndef DEBUG
  freopen("cycles.in", "r", stdin);
  freopen("cycles.out", "w", stdout);
#endif
  uint32_t n, m;
  cin >> n >> m;
  vector<pair<uint32_t, uint32_t>> weights(n);
  for (uint32_t i = 0; i != n; ++i) {
    cin >> weights[i].first;
    weights[i].second = i;
  }

  uint32_t cnt, tmp;
  bitset<20> set;
  while (m--) {
    set.reset();
    cin >> cnt;
    while (cnt--) {
      cin >> tmp;
      set.set(tmp - 1);
    }
    bitmask_dfs(set);
  }

  sort(weights.begin(), weights.end());
  set.reset();
  uint32_t weight = 0;
  while (!weights.empty()) {
    weight += weights.rbegin()->first;
    set.set(weights.rbegin()->second);
    if (dependent.find(set) != dependent.end()) {
      weight -= weights.rbegin()->first;
      set.reset(weights.rbegin()->second);
    }
    weights.pop_back();
  }

  cout << weight;
  return 0;
}