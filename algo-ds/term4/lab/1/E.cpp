//
// Created by covariance on 14.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> dzeta(const string &str) {
  uint32_t n = str.size();
  vector<uint32_t> z(n);
  z[0] = 0;
  for (uint32_t i = 1, l = 0, r = 0; i != n; ++i) {
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && !(str[z[i]] ^ str[i + z[i]])) {
      ++z[i];
    }
    if (i + z[i] > r + 1) {
      l = i, r = i + z[i] - 1;
    }
  }

  return z;
}

int main() {
  string text, w;
  cin >> w >> text;

  string template_1 = w + '#' + text;
  vector<uint32_t> pf = dzeta(template_1);

  reverse(text.begin(), text.end());
  reverse(w.begin(), w.end());

  string template_2 = w + '#' + text;
  vector<uint32_t> zf = dzeta(template_2), result;

  for (uint32_t i = 0; i + w.size() != text.size() + 1; ++i) {

    if (template_2.size() < i + w.size()) {
      cout << 0;
      return 0;
    }

    if (pf[w.size() + 1 + i] + 1 + zf[template_2.size() - i - w.size()] >= w.size()) {
      result.push_back(i + 1);
    }
  }

  cout << result.size() << endl;
  for (uint32_t x: result) {
    cout << x << " ";
  }
  return 0;
}
