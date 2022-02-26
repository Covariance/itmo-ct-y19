//
// Created by covariance on 03.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<int> ans;

bool query(int a, int b) {
  assert(a != b);
  cout << "1 " << a << ' ' << b << endl;
  string s;
  cin >> s;
  return (s == "YES");
}

void win() {
  cout << 0;
  for (int i : ans) {
    cout << ' ' << i;
  }
  cout << endl;
}

void add_lamp(int cur) {
  int l = -1, r = cur - 1;
  static std::string res;
  while (r - l > 1) {
    int m = l + (r - l) / 2;

    if (query(ans[m], cur)) {
      l = m;
    } else {
      r = m;
    }
  }
  ans.insert(ans.begin() + r, cur);
}

int main() {
  int n;
  cin >> n;

  ans.push_back(1);
  for (int i = 2; i != n + 1; ++i) {
    add_lamp(i);
  }
  win();
  return 0;
}
