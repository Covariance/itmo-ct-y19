//
// Created by covariance on 24.02.2021.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;

  vector<uint32_t> pi(s.size());
  pi[0] = 0;
  for (uint32_t i = 1, k = 0; i != s.size(); i++) {
    while (k > 0 && s[k] != s[i]) {
      k = pi[k - 1];
    }
    pi[i] = s[k] == s[i] ? ++k : k;
  }

  for (auto v : pi) {
    cout << v << ' ';
  }
  return 0;
}
