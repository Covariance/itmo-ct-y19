//
// Created by covariance on 03.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> matrix;
deque<int> ans;

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

  for (int k = 0; k != 2 * n; ++k) {
    if (!matrix[ans[0]][ans[1]]) {
      int i = 2;
      while (!matrix[ans[0]][ans[i]] || !matrix[ans[1]][ans[i + 1]]) {
        ++i;
      }
      reverse(ans.begin() + 1, ans.begin() + i + 1);
    }
    ans.push_back(ans.front());
    ans.pop_front();
  }

  for (auto i : ans) {
    cout << i + 1 << ' ';
  }

  return 0;
}