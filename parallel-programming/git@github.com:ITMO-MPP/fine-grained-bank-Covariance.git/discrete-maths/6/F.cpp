//
// Created by covariance on 04.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int n;

vector<pair<int, int>> solve(const vector<int> &prufer_code) {
  vector<int> degree(n, 1);
  for (int i : prufer_code) {
    ++degree[i];
  }

  set<int> leaves;
  for (int i = 0; i < n; ++i) {
    if (degree[i] == 1) {
      leaves.insert(i);
    }
  }

  vector<pair<int, int>> result;
  for (int i = 0; i + 2 != n; ++i) {
    int leaf = *leaves.begin();
    leaves.erase(leaves.begin());

    int parent = prufer_code[i];
    --degree[parent];

    result.emplace_back(leaf, parent);

    if (degree[parent] == 1) {
      leaves.insert(parent);
    }
  }
  int pre_last = *leaves.begin();
  leaves.erase(leaves.begin());
  int last = *leaves.begin();
  result.emplace_back(last, pre_last);
  return result;
}

int main() {
  cin >> n;

  vector<int> prufer(n - 2);
  for (int i = 0; i + 2 != n; ++i) {
    cin >> prufer[i];
    --prufer[i];
  }

  for (auto i : solve(prufer)) {
    cout << i.first + 1 << ' ' << i.second + 1 << '\n';
  }

  return 0;
}