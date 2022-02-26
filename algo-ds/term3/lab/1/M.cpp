//
// Created by covariance on 28.09.2020.
//
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define fs first
#define sc second

using namespace std;

vector<vector<int>> g;
vector<int> used;
vector<string> order;
vector<int> result;

bool dfs(int i) {
  switch (used[i]) {
    case WHITE:
      used[i] = GRAY;
      for (int son : g[i]) {
        if (!dfs(son)) {
          return false;
        }
      }
      used[i] = BLACK;
      result.emplace_back(i);
      return true;
    case BLACK:
      return true;
    default:
      return false;
  }
}

int main() {
  int m;
  cin >> m;

  g.resize(27);
  used.assign(27, WHITE);
  order.resize(m);

  for (int i = 0; i != m; ++i) {
    cin >> order[i];
    if (order[i].size() > 1) {
      g[0].push_back(order[i][0] - 'a' + 1);
    }
  }

  for (int i = 1; i != m; ++i) {
    size_t cur_len = order[i].length(), last_len = order[i - 1].length();
    if (cur_len < last_len || order[i] == order[i - 1]) {
      cout << "No";
      return 0;
    }
    if (cur_len == last_len) {
      for (size_t j = 0; j != cur_len; ++j) {
        if (order[i][j] != order[i - 1][j]) {
          g[order[i - 1][j] - 'a' + 1].push_back(order[i][j] - 'a' + 1);
          break;
        }
      }
    }
  }

  for (int i = 0; i != 27; ++i) {
    if (!dfs(i)) {
      cout << "No";
      return 0;
    }
  }

  reverse(result.begin(), result.end());

  set<pair<int, int>> final;
  for (int i = 0; i != 27; ++i) {
    final.insert({result[i], i});
  }
  if (final.begin()->sc == 0) {
    cout << "No";
    return 0;
  }
  cout << "Yes\n";
  for (auto i = ++final.begin(); i != final.end(); i++) {
    cout << i->sc - (i->sc < final.begin()->sc ? 0 : 1) << ' ';
  }
  return 0;
}
