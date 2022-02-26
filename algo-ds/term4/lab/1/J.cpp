//
// Created by covariance on 14.03.2021.
//

#include <bits/stdc++.h>

using namespace std;
int count_prefix(vector<uint32_t> &result, const vector<char> &str) {
  uint32_t mx = 0;

  result[0] = 0;
  for (size_t i = 1; i < str.size(); i++) {
    uint32_t l = result[i - 1];

    while (l != 0 && str[l] != str[i]) {
      l = result[l - 1];
    }

    l += (str[l] == str[i]);
    result[i] = l;
    mx = max(result[i], mx);
  }
  return mx;
}

int main() {
  string text;
  cin >> text;

  vector<char> s(1, text[0]);
  uint64_t res = 1;
  cout << res << '\n';

  vector<uint32_t> pf(text.size(), 0);
  for (size_t i = 1; i != text.size(); ++i) {
    s.insert(s.begin(), text[i]);
    cout << (res = (res + s.size() - count_prefix(pf, s))) << '\n';
  }
}