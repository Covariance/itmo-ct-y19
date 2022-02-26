//
// Created by covariance on 15.04.2021.
//

#include <bits/stdc++.h>
#define MOD 998244353l

using namespace std;

int64_t get(const vector<int64_t> &v, uint32_t i) {
  return i >= v.size() ? 0 : v[i];
}

int main() {
  uint32_t n, m;
  cin >> n >> m;
  vector<int64_t> p(n + 1), q(m + 1);
  for (auto &i : p) {
    cin >> i;
  }
  for (auto &i : q) {
    cin >> i;
  }

  cout << max(n, m) << endl;
  for (uint32_t i = 0; i <= max(n, m); ++i) {
    cout << (get(p, i) + get(q, i)) % MOD << ' ';
  }
  cout << endl;


  cout << n + m << endl;
  for (uint32_t i = 0; i <= n + m; i++) {
    int64_t c = 0;
    for (uint32_t j = 0; j <= i; j++) {
      c = (c + get(q, j) * get(p, i - j)) % MOD;
    }
    cout << c << ' ';
  }
  cout << endl;

  vector<int64_t> cv;
  for (uint32_t i = 0; i != 1000; ++i) {
    int64_t c = get(p, i);
    for (uint32_t j = 0; j != i; ++j) {
      c = (c + MOD - get(q, i - j) * get(cv, j)) % MOD;
    }
    cv.push_back((c + MOD) % MOD);
  }

  for (auto &i : cv) {
    cout << i << ' ';
  }

  return 0;
}