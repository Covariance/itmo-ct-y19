//
// Created by covariance on 17.04.2021.
//

#include <bits/stdc++.h>
#define MOD 104857601l

using namespace std;

uint64_t n, k;

int64_t shift(vector<int64_t> &a, vector<int64_t> &c) {
  vector<int64_t> r(k + 1);
  vector<int64_t> neg_q(k + 1);

  while (n >= k) {
    for (uint32_t i = k; i != a.size(); ++i) {
      a[i] = 0;
      for (uint32_t j = 1; j != c.size(); ++j) {
        a[i] = (a[i] - c[j] * a[i - j]) % MOD;
        while (a[i] < 0) {
          a[i] += MOD;
        }
      }
    }

    for (uint32_t i = 0; i < c.size(); i += 2) {
      neg_q[i] = c[i];
    }
    for (uint32_t i = 1; i < c.size(); i += 2) {
      neg_q[i] = (MOD - c[i]) % MOD;
    }

    for (uint32_t i = 0; i <= 2 * k; i += 2) {
      int64_t cr = 0;
      for (uint32_t j = 0; j <= i; ++j) {
        int64_t qq = (j > k ? 0 : c[j]);
        int64_t neq = (i - j > k ? 0 : neg_q[i - j]);

        cr = (cr + qq * neq + MOD) % MOD;
      }
      r[i / 2] = cr;
    }

    c = r;
    int freeI = 0;
    for (uint32_t i = 0; i != a.size(); ++i) {
      if ((i & 1) == (n & 1)) {
        a[freeI++] = a[i];
      }
    }

    n /= 2;
  }
  return a[n];
}

int main() {
  cin >> k >> n;
  n--;

  vector<int64_t> a(k);
  vector<int64_t> c(k);

  for (auto &i : a) {
    cin >> i;
  }
  a.resize(2 * k);

  for (auto &i : c) {
    cin >> i;
  }
  transform(c.begin(), c.end(), c.begin(), [](int64_t &a) -> int64_t { return (MOD - a) % MOD; });
  c.insert(c.begin(), 1);

  cout << shift(a, c);
  return 0;
}
