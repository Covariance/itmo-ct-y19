//
// Created by covariance on 20.10.2020.
//
#include <bits/stdc++.h>

#define INF 1e9 + 7
#define fs first
#define sc second

using namespace std;

vector<vector<int>> g;
vector<bool> used;

void dfs(int v, int p) {
  if (used[v]) {
    return;
  }
  used[v] = true;
  for (int son : g[v]) {
    if (son != p) {
      dfs(son, v);
    }
  }
}

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

  vector<pair<int, pair<int, int>>> edges(m);
  g.assign(n, vector<int>());
  used.assign(n, false);

  for (int i = 0; i != m; ++i) {
    int from, to, w;
    cin >> from >> to >> w;
    edges[i] = {w, {--from, --to}};
    g[from].push_back(to);
    g[to].push_back(from);
  }

  dfs(0, -1);
  for (bool touch : used) {
    if (!touch) {
      cout << "NO\n";
      return 0;
    }
  }

  sort(edges.begin(), edges.end());

  int ans = 2 * INF;

  for (int i = 0; i != m; ++i) {
    dsu cyc(n);
    int min_edge = INF, max_edge = -INF, cnt = n - 1;

    for (int j = i; j != m && cnt != 0; ++j) {
      if (cyc.find(edges[j].sc.fs) != cyc.find(edges[j].sc.sc)) {
        cyc.unite(edges[j].sc.fs, edges[j].sc.sc);
        --cnt;
        min_edge = min(min_edge, edges[j].fs);
        max_edge = max(max_edge, edges[j].fs);
      }
    }

    if (cnt == 0) {
      ans = min(ans, max_edge - min_edge);
    }
  }
  cout << "YES\n" << ans;
  return 0;
}
