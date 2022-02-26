//
// Created by covariance on 16.04.2021.
//

#include <bits/stdc++.h>
#define MOD 998244353l

using namespace std;

int64_t get(const vector<int64_t> &v, uint32_t i) {
  return i >= v.size() ? 0 : v[i];
}

int main() {
  uint32_t n;
  cin >> n;

  vector<int64_t> a(n);
  for (auto &i : a) {
    cin >> i;
  }

  int64_t tmp;
  vector<int64_t> q;
  q.reserve(n + 1);
  q.push_back(1);
  for (uint32_t i = 0; i != n; ++i) {
    cin >> tmp;
    q.push_back(-tmp);
  }

  vector<int64_t> p;
  for (uint32_t i = 0; i != n; ++i) {
    int64_t c = 0;
    for (uint32_t j = 0; j <= i; ++j) {
      c += a[j] * q[i - j];
    }
#ifdef DEBUG
    cout << '!' << c << endl;
#endif
    p.push_back(c);
  }
  while (p.back() == 0) {
    p.pop_back();
  }

  cout << p.size() - 1 << endl;
  for (auto &i : p) {
    cout << i << ' ';
  }

  cout << endl << n << endl;
  for (auto &i : q) {
    cout << i << ' ';
  }
  cout << endl;
  return 0;
}