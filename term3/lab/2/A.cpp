//
// Created by covariance on 17.10.2020.
//

#include <bits/stdc++.h>
#define INF 1e9 + 7

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> g(n, vector<int>());
  vector<int> d(n, INF);

  while (m--) {
    int from, to;
    cin >> from >> to;
    g[--from].push_back(--to);
    g[to].push_back(from);
  }

  queue<int> bfs;
  d[0] = 0;
  bfs.push(0);

  while (!bfs.empty()) {
    int cur = bfs.front();
    bfs.pop();
    for (int son : g[cur]) {
      if (d[son] == INF) {
        d[son] = d[cur] + 1;
        bfs.push(son);
      }
    }
  }

  for (int res : d) {
    cout << res << ' ';
  }

  return 0;
}
