//
// Created by covariance on 19.12.2020.
//
#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> hungarian(const vector<vector<int>> &matrix) {
  size_t n = matrix.size();
  int end;
  vector<int> row(n + 1, 0), col(n + 1, 0);
  vector<int> marked(n + 1), links(n + 1), mins(n + 1);
  vector<bool> visited(n + 1);

  for (size_t i = 1; i <= n; ++i) {
    fill(mins.begin(), mins.end(), numeric_limits<int>::max());
    fill(visited.begin(), visited.end(), false);

    marked[0] = i, end = 0;
    do {
      visited[end] = true;
      int cur_min = numeric_limits<int>::max(), mj = 0, next_v = marked[end];

      for (size_t to = 1; to <= n; ++to) {
        if (!visited[to] && matrix[next_v - 1][to - 1] < col[next_v] + row[to] + mins[to]) {
          mins[to] = matrix[next_v - 1][to - 1] - col[next_v] - row[to];
          links[to] = end;
        }
      }

      for (size_t to = 1; to <= n; ++to) {
        if (!visited[to] && mins[to] < cur_min) {
          cur_min = mins[to];
          mj = to;
        }
      }

      for (size_t to = 0; to <= n; ++to) {
        if (visited[to]) {
          col[marked[to]] += cur_min;
          row[to] -= cur_min;
        }
      }

      for (size_t to = 0; to <= n; ++to) {
        if (!visited[to]) {
          mins[to] -= cur_min;
        }
      }

      end = mj;
    } while (marked[end] != 0);

    do {
      int next = links[end];
      marked[end] = marked[next];
      end = next;
    } while (end != 0);
  }

  vector<pair<int, int>> res;
  res.reserve(n);
  for (size_t i = 1; i <= n; ++i) {
    res.emplace_back(marked[i], i);
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  vector<vector<int>> matrix(n, vector<int>(n));
  for (auto &row : matrix) {
    for (auto &item : row) {
      cin >> item;
    }
  }

  auto res = hungarian(matrix);
  cout << accumulate(res.begin(), res.end(), 0,
                     [matrix](const int &a, const pair<int, int> &b) -> int {
                       return a + matrix[b.first - 1][b.second - 1];
                     }) << endl;
  sort(res.begin(), res.end());
  for (auto i : res) {
    cout << i.first << ' ' << i.second << endl;
  }

  return 0;
}
