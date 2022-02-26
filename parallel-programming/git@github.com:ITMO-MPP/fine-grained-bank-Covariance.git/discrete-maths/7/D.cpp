//
// Created by covariance on 22.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
#ifndef DEBUG
  freopen("check.in", "r", stdin);
  freopen("check.out", "w", stdout);
#endif
  uint32_t n, m, tmp;
  cin >> n >> m;
  vector<bitset<10>> independent(m, bitset<10>());
  for (auto &set : independent) {
    cin >> n;
    while (n--) {
      cin >> tmp;
      set.set(tmp - 1);
    }
  }

  // check empty
  if (find(independent.begin(), independent.end(), bitset<10>()) == independent.end()) {
    cout << "NO\n";
    return 0;
  }

  // check subsets
  for (auto set : independent) {
    for (uint32_t i = 0; i != 10u; ++i) {
      if (set.test(i)) {
        set.flip(i);
        if (find(independent.begin(), independent.end(), set) == independent.end()) {
          cout << "NO\n";
          return 0;
        }
        set.flip(i);
      }
    }
  }

  // check inclusions
  uint32_t mx = max_element(independent.begin(),
                            independent.end(),
                            [](const bitset<10> &lhs, const bitset<10> &rhs) -> bool {
                              return lhs.count() < rhs.count();
                            })->count();
  vector<bitset<10>> bases;
  copy_if(independent.begin(),
          independent.end(),
          back_inserter(bases),
          [mx](const bitset<10> &i) -> bool { return i.count() == mx; });

  for (auto set : independent) {
    if (set.count() < mx) {
      for (auto &base : bases) {
        bitset<10> check = (base & (~set));
        bool found = false;
        for (uint32_t i = 0; i != 10u; ++i) {
          if (check.test(i)) {
            set.set(i);
            found |= (find(independent.begin(), independent.end(), set) != independent.end());
            set.reset(i);
          }
        }
        if (!found) {
          cout << "NO\n";
          return 0;
        }
      }
    }
  }

  cout << "YES\n";
  return 0;
}