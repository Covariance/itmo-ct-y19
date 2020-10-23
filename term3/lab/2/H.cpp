//
// Created by covariance on 19.10.2020.
//
#include <bits/stdc++.h>

#define INF 1e9 + 7
#define fs first
#define sc second

using namespace std;

class dsu {
  vector<int> rank;
  vector<int> p;

 public:
  explicit dsu(int n)
    : rank(n, 0)
    , p(n) {
    for (int i = 0; i != n; ++i) {
      p[i] = i;
    }
  }

  int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
  }

  void unite(int x, int y) {
    if ((x = find(x)) == (y = find(y))) {
      return;
    }
    if (rank[x] < rank[y]) {
      p[x] = y;
    } else {
      p[y] = x;
      if (rank[x] == rank[y]) {
        ++rank[x];
      }
    }
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  dsu cyc(n);
  vector<pair<int, pair<int, int>>> q(m);

  for (int i = 0; i != m; ++i) {
    int from, to, w;
    cin >> from >> to >> w;
    q[i] = {w, {--from, --to}};
  }

  sort(q.begin(), q.end());

  long long sum = 0L;

  for (auto& edge : q) {
    if (cyc.find(edge.sc.fs) != cyc.find(edge.sc.sc)) {
      sum += edge.fs;
      cyc.unite(edge.sc.fs, edge.sc.sc);
    }
  }

  cout << sum;

  return 0;
}
