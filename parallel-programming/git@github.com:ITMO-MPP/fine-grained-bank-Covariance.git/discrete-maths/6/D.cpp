//
// Created by covariance on 03.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> g;
vector<int> path;
vector<int> cycle;

void add_to_path(int v) {
  auto it = path.begin();
  while (it != path.end() && g[*it][v]) {
    ++it;
  }
  path.insert(it, v);
}

int main() {
  int n;
  char c;
  cin >> n;
  g.assign(n, vector<bool>(n, false));

  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != i; ++j) {
      cin >> c;
      g[j][i] = !(g[i][j] = (c == '1'));
    }
  }

  vector<int> order(n);
  for (int i = 0; i != n; ++i) {
    order[i] = i;
  }

  while (true) {
    path.clear();
    path.push_back(order[0]);
    for (int i = 1; i != n; ++i) {
      add_to_path(order[i]);
    }
    if (g[path[path.size() - 1]][path[0]]) {
      break;
    } else {
      shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
    }
  }

  for (int cv : path) {
    cout << cv + 1 << ' ';
  }

  return 0;
}
