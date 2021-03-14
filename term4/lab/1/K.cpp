//
// Created by covariance on 14.03.2021.
//
#include <bits/stdc++.h>
using namespace std;

string s;

vector<int> build_p(uint32_t from, uint32_t count) {
  uint32_t j = 0;
  vector<int> p(count);
  for (uint32_t i = 1; i != count; ++i) {
    while(j && s[from + i] != s[from + j]) {
      j = p[j - 1];
    }
    p[i] = (s[from + i] == s[from + j] ? ++j : j);
  }
  return p;
}

int main() {
  cin >> s;

  uint32_t n = s.size();

  vector<vector<int>> p(n);
  for (uint32_t i = 0; i != n; ++i) {
    p[i] = build_p(i, n - i);
  }
  vector<vector<int>> mss(n), c(n);
  for (uint32_t i = 0; i != n; ++i) {
    mss[i].resize(p[i].size());
    for (uint32_t j = 1; j != p[i].size(); ++j) {
      mss[i][j] = max(mss[i][j - 1], p[i][j]);
    }
    c[i].resize(p[i].size());
  }

  for (uint32_t i = n; i != 0; --i) {
    c[i - 1][0] = 1;
    for (uint32_t j = i - 1; j != 0; --j) {
      c[j - 1][i - j] = c[j][i - j - 1] + i - j + 1 - mss[j - 1][i - j];
    }
  }

  uint32_t q, l, r;
  cin >> q;

  while (q--) {
    cin >> l >> r;
    cout << c[l - 1][r - l] << endl;
  }
  return 0;
}
