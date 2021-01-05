//
// Created by covariance on 03.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> matrix;
deque<int> ans;

bool check() {
  for (size_t i = 1; i != ans.size(); ++i) {
    if (!matrix[ans[i - 1]][ans[i]]) {
      return false;
    }
  }
  return matrix[ans[0]][ans[ans.size() - 1]];
}

void build() {
  for (int k = 0; k != 10 * ans.size(); ++k) {
    if (!matrix[ans[0]][ans[1]]) {
      int i = 2;
      while (i + 1 != ans.size() && (!matrix[ans[0]][ans[i]] || !matrix[ans[1]][ans[i + 1]])) {
        ++i;
      }
      reverse(ans.begin() + 1, ans.begin() + i + 1);
    }
    ans.push_back(ans.front());
    ans.pop_front();
  }
}

int main() {
  int n;
  string s;
  cin >> n;
  matrix.assign(n, vector<bool>(n));

  for (int i = 1; i != n; ++i) {
    cin >> s;
    for (int j = 0; j != i; ++j) {
      matrix[i][j] = matrix[j][i] = (s[j] == '1');
    }
  }

  for (int i = 0; i != n; ++i) {
    ans.push_back(i);
  }

  while (true) {
    build();
    if (check()) {
      break;
    } else {
      shuffle(ans.begin(), ans.end(), std::mt19937(std::random_device()()));
    }
  }

  for (auto i : ans) {
    cout << i + 1 << ' ';
  }

  return 0;
}