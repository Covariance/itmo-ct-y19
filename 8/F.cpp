//
// Created by covariance on 18.04.2021.
//

#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

int main() {
  uint32_t k, m;
  cin >> k >> m;

  vector<bool> nodes(m + 1, false);
  vector<int64_t> trees(m + 1, 0), pref(m + 1, 0);
  trees[0] = pref[0] = 1;

  for (uint32_t i = 0; i != k; ++i) {
    uint32_t node;
    cin >> node;
    nodes[node] = true;
  }

  for (uint32_t i = 1; i != m + 1; ++i) {
    int64_t sum = 0;
    for (uint32_t j = 1; j <= i; ++j) {
      if (nodes[j]) {
        sum += pref[i - j] % MOD;
      }
    }
    trees[i] = sum % MOD;

    for (uint32_t j = 0; j <= i; ++j) {
      pref[i] = (pref[i] + trees[j] * trees[i - j]) % MOD;
    }

    cout << trees[i] << ' ';
  }

  return 0;
}