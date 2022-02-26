//
// Created by covariance on 14.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> dzeta(const string &str) {
  uint32_t n = str.size();
  vector<uint32_t> z(n);
  z[0] = 0;
  for (uint32_t i = 1, l = 0, r = 0; i != n; ++i) {
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && !(str[z[i]] ^ str[i + z[i]])) {
      ++z[i];
    }
    if (i + z[i] > r + 1) {
      l = i, r = i + z[i] - 1;
    }
  }

  return z;
}

int main() {
  string s;
  cin >> s;

  vector<uint32_t> zf = dzeta(s);
  for (size_t i = 1; i != s.size(); ++i) {
    if (s.size() % i == 0 && zf[i] + i == s.size()) {
      cout << i;
      return 0;
    }
  }
  cout << s.size();
  return 0;
}