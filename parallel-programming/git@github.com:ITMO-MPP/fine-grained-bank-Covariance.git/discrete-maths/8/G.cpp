//
// Created by covariance on 17.04.2021.
//

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;

struct pair_hash {
  size_t operator () (const pair<int64_t, int64_t> &p) const {
    return 31 * p.first + p.second;
  }
};

unordered_map<pair<int64_t, int64_t>, int64_t, pair_hash> prec;

int64_t C(int64_t n, int64_t k) {
  if (prec.find({n, k}) != prec.end()) {
    return prec[{n, k}];
  }
  int64_t res = 1;
  for (uint32_t i = n - k + 1; i <= n; ++i) {
    res *= i;
  }
  for (uint32_t i = 2; i <= k; ++i) {
    res /= i;
  }
  return prec[{n, k}] = res;
}

vector<int64_t> parse(const string &s, uint32_t &pos) {
  vector<int64_t> res(7);
  switch (s[pos]) {
    case 'B': {
      ++pos;
      res = {0, 1, 0, 0, 0, 0, 0};
      break;
    }
    case 'L': {
      pos += 2;
      auto inner = parse(s, pos);
      res[0] = 1;
      for (uint32_t i = 1; i != 7; ++i) {
        int64_t sum = 0;
        for (uint32_t j = 1; j <= i; ++j) {
          sum += inner[j] * res[i - j];
        }
        res[i] = sum;
      }
      break;
    }
    case 'S': {
      pos += 2;
      auto inner = parse(s, pos);

      vector<vector<int64_t>> matrix(7, vector<int64_t>(7));

      matrix[0][0] = 1;

      for (int i = 1; i < matrix.size(); i++) {
        matrix[0][i] = 1;
        matrix[i][0] = 0;
      }

      res[0] = 1;
      for (uint32_t i = 1; i != 7; ++i) {
        for (int j = 1; j != 7; ++j) {
          long long sum = 0;
          for (int k = 0; k <= i / j; ++k) {
            sum += C(max(inner[j] + k - 1, static_cast<int64_t>(0)), k) * matrix[i - k * j][j - 1];
          }
          matrix[i][j] = sum;
        }
        res[i] = matrix[i][i];
      }
      break;
    }
    case 'P': {
      pos += 2;
      auto inner1 = parse(s, pos);
      auto inner2 = parse(s, pos);
      for (uint32_t i = 0; i != 7; ++i) {
        int64_t sum = 0;
        for (int j = 0; j <= i; j++) {
          sum += inner1[j] * inner2[i - j];
        }
        res[i] = sum;
      }
      break;
    }
  }
  ++pos;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string line;
  uint32_t pos = 0;
  getline(cin, line);
  for (auto &i : parse(line, pos)) {
    cout << i << ' ';
  }
  return 0;
}