//
// Created by covariance on 19.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000000000007L

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<long long>> d(n, vector<long long>(n, INF));

  for (int i = 0; i != m; ++i) {
    int from, to;
    long long w;
    cin >> from >> to >> w;
    --from;
    --to;
    d[from][to] = min(d[from][to], w);
  }

  for (int i = 0; i != n; ++i) {
    d[i][i] = 0;
  }

  for (int k = 0; k != n; ++k) {
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != n; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  for (const auto& line : d) {
    for (const auto& el : line) {
      cout << el << ' ';
    }
    cout << "\n";
  }
}
