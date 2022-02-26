//
// Created by covariance on 14.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
  string str;
  cin >> str;

  vector<uint64_t> pows(str.size());

  pows[0] = 1;
  uint64_t p = 1000000007;
  for (size_t i = 1; i != pows.size(); i++) {
    pows[i] = pows[i - 1] * p;
  }

  vector<uint64_t> hash(str.size());
  hash[0] = str[0] - '8' + 1;
  for (size_t i = 1; i != hash.size(); i++) {
    hash[i] = hash[i - 1] + (str[i] - '8' + 1) * pows[i];
  }

  size_t q;
  cin >> q;

  for (size_t i = 0; i != q; ++i) {
    size_t a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a > c) {
      swap(a, c);
      swap(b, d);
    }

    uint64_t h_ab = hash[b - 1];
    if (a != 1) {
      h_ab -= hash[a - 2];
    }

    uint64_t h_cd = hash[d - 1];
    if (c != 1) {
      h_cd -= hash[c - 2];
    }

    cout << ((h_ab * pows[c - a] == h_cd) ? "Yes\n" : "No\n");
  }
}
