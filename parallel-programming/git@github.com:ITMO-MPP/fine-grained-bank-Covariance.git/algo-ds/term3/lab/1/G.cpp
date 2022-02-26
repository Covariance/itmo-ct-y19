//
// Created by covariance on 07.09.2020.
//
#include <bits/stdc++.h>

#define fs first
#define sc second

using namespace std;

vector<vector<int>> g;
vector<int> comp;

void dfs(int v, int num) {
  if (comp[v] != 0) {
    return;
  }
  comp[v] = num;
  for (int son : g[v]) {
    dfs(son, num);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  comp.assign(n, 0);
  g.resize(n);
  int cnt = 1;
  for (; m != 0; --m) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (; n != 0; --n) {
    if (comp[n - 1] == 0) {
      dfs(n - 1, cnt++);
    }
  }

  cout << cnt - 1 << endl;
  for (int i : comp) {
    cout << i << ' ';
  }

  return 0;
}
