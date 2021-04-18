//
// Created by covariance on 18.04.2021.
//

#include <iostream>
#include <vector>
#define MOD 998244353l

using namespace std;

// Thanks to e-maxxx for this beautiful algorithm
int64_t gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int64_t x1, y1;
  int64_t d = gcd(b % a, a, x1, y1);
  x = (y1 - ((b / a) * x1));
  y = x1;
  return d;
}

int64_t reverseElement(int64_t a) {
  int64_t x, y, d;
  d = gcd(a, MOD, x, y);
  if (d != 1) {
    return 1;
  } else {
    return (x % MOD + MOD) % MOD;

  }
}

vector<vector<int64_t>> pows;

vector<int64_t> multiply(const vector<int64_t> &lhs, const vector<int64_t> &rhs) {
  vector<int64_t> res(101, 0);
  for (uint32_t i = 0; i != res.size(); ++i) {
    int64_t mul = 0;
    for (uint32_t j = 0; j <= i; ++j) {
      mul = (mul + (lhs[j] * rhs[i - j] % MOD)) % MOD;
    }
    res[i] = mul;
  }
  return res;
}

void substitution(const vector<int64_t> &coefs) {

  for (uint32_t i = 0; i != 101; ++i) {
    int64_t coef = 0;
    for (uint32_t j = 0; j != 101; ++j) {
      int64_t coefJI = coefs[j] * pows[j][i];
      coefJI %= MOD;
      coef += coefJI;
      coef %= MOD;
    }
    cout << coef << ' ';
  }
}

int main() {
  uint64_t n, m;
  cin >> n >> m;

  vector<int64_t> expCoefs(101, 0);
  vector<int64_t> logCoefs(101, 0);
  vector<int64_t> sqrtCoefs(101, 0);

  sqrtCoefs[0] = expCoefs[0] = logCoefs[1] = 1;

  for (int i = 1; i <= 100; i++) {
    expCoefs[i] = (reverseElement(i) * expCoefs[i - 1]) % MOD;
    sqrtCoefs[i] = (((((MOD - sqrtCoefs[i - 1]) % MOD)
        * (((2 * i - 1) * (2 * i) * (3 - 2 * i) + MOD) % MOD)) % MOD)
        * (reverseElement((i * i * 4 * (1 - 2 * i) + MOD) % MOD)) % MOD);
  }

  for (uint32_t i = 2; i <= 100; ++i) {
    logCoefs[i] = ((((MOD - logCoefs[i - 1]) % MOD) * (i - 1) % MOD) * reverseElement(i)) % MOD;
  }

  vector<int64_t> p(101, 0);
  vector<int64_t> q(101, 0);
  q[0] = 1;

  int64_t tmp;
  for (int i = 0; i <= n; ++i) {
    cin >> tmp;
    p[i] = tmp;
  }

  pows.push_back(q);
  pows.push_back(p);

  for (int i = 2; i <= 100; ++i) {
    pows.push_back(multiply(p, pows[i - 1]));
  }

  substitution(sqrtCoefs);
  cout << endl;
  substitution(expCoefs);
  cout << endl;
  substitution(logCoefs);
  cout << endl;

  return 0;
}