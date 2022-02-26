//
// Created by covariance on 14.03.2021.
//
#include <bits/stdc++.h>
#include <numeric>
#define mod static_cast<uint64_t>(1e+9 + 7)

using namespace std;

int main() {
  uint64_t n, m;
  cin >> n >> m;
  vector<uint32_t> p(static_cast<size_t>(n));
  for (uint32_t i = 1; i != n; ++i) {
    cin >> p[i];
  }

  vector<uint64_t> cnt(static_cast<size_t>(n), static_cast<uint64_t>(1));
  cnt[0] = m;

  for (uint32_t i = 1; i != n; ++i) {
    if (p[i] == 0) {

      uint64_t cur = m;
      uint32_t j = p[i - 1];
      while (j) {
        if (p[j] == 0) {
          --cur;
        }
        j = p[j - 1];
      }
      cnt[i] = --cur;
    }
  }

  cout << accumulate(cnt.begin(),
                 cnt.end(),
                 1,
                 [](const uint64_t &l, const uint64_t &r) -> uint64_t { return (l * r) % mod; })
       << endl;
}