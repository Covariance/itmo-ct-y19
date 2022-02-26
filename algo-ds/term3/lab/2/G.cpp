//
// Created by covariance on 19.10.2020.
//
#include <bits/stdc++.h>

#define INF 1e9 + 7
#define fs first
#define sc second

using namespace std;

vector<pair<int, int>> vert;

int calc_weight(int x, int y) {
  return (vert[x].fs - vert[y].fs) * (vert[x].fs - vert[y].fs) +
         (vert[x].sc - vert[y].sc) * (vert[x].sc - vert[y].sc);
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i != n; ++i) {
    int x, y;
    cin >> x >> y;
    vert.emplace_back(x, y);
  }

  vector<int> min_enter(n, INF);
  vector<bool> used(n, false);
  used[0] = true;

  for (int i = 1; i != n; ++i) {
    min_enter[i] = min(calc_weight(0, i), min_enter[i]);
  }

  long double sum = 0;

  for (int t = 1; t != n; ++t) {
    int min_vert = 0, min_val = INF;
    for (int i = 0; i != n; ++i) {
      if (!used[i] && min_enter[i] < min_val) {
        min_val = min_enter[i];
        min_vert = i;
      }
    }

    used[min_vert] = true;
    sum += sqrtl((long double) min_val);

    for (int i = 0; i != n; ++i) {
      if (!used[i]) {
        min_enter[i] = min(calc_weight(i, min_vert), min_enter[i]);
      }
    }
  }

  cout << setprecision(20) << sum;

  return 0;
}
