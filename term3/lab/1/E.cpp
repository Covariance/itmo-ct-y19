//
// Created by covariance on 07.09.2020.
//
#include <bits/stdc++.h>

#define fs first
#define sc second

#define UNTOUCHED 0
#define ENTERED 1
#define LEFT 2

#define OK -1

using namespace std;

vector<vector<int>> g;
vector<int> state;
vector<int> cycle;

int dfs(int v) {
  if (state[v] == LEFT) {
    return OK;
  }
  if (state[v] == UNTOUCHED) {
    cycle.push_back(v);
    state[v] = ENTERED;
    for (int son : g[v]) {
      int res = dfs(son);
      if (res != OK) {
        return res;
      }
    }
    cycle.pop_back();
    state[v] = LEFT;
    return OK;
  }
  return v;
}

int main() {
  int n, m;
  cin >> n >> m;
  state.assign(n, UNTOUCHED);
  g.resize(n);

  for (; m != 0; --m) {
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
  }

  for (; n != 0; --n) {
    if (state[n - 1] == UNTOUCHED) {
      int res = dfs(n - 1);
      if (res != OK) {
        cout << "YES\n";
        cycle.erase(cycle.begin(), find(cycle.begin(), cycle.end(), res));
        for (int node : cycle) {
          cout << node  + 1 << " ";
        }
        return 0;
      }
    }
  }
  cout << "NO" << endl;
  return 0;
}
