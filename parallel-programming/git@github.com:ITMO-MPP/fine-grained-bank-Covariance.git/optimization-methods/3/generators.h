#ifndef SOLE_SOLVER_GENERATORS_H
#define SOLE_SOLVER_GENERATORS_H

#include <full_matrix.h>
#include <sparse_matrix.h>
#include <random>
#include <vector>

using ld = long double;

const int SEED = 1838128;
std::mt19937 rnd(SEED);

std::pair<full_matrix<ld>, std::vector<ld>> genSOLE(int n, ld maxValue) {
  full_matrix<ld> answer(n, 1);
  std::uniform_real_distribution<> random(-maxValue, maxValue);
  for (int i = 0; i < n; i++) {
    answer.set(i, 0, random(rnd));
  }
  full_matrix<ld> a(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a.set(i, j, random(rnd));
    }
  }
  auto bMatrix = mul(a, answer);
  std::vector<ld> b(n);
  for (int i = 0; i < n; i++) {
    b[i] = bMatrix.get(i, 0);
  }
  return {a, b};
}

sparse_matrix<ld> gen_sparse(int n, int diag, ld add_to_first = 1, bool is_symmetric = false) {
  sparse_matrix<ld> a(n);
  for (int i = 0; i < n; i++) {
    ld sum = 0;
    for (int j = std::max(0, i - diag); j <= std::min(i + diag, n - 1); j++) {
      if (i != j) {
        ld x = -(int) (rnd() % 5);
        a.set(i, j, x);
        sum -= x;
      }
    }
    a.set(i, i, sum + (i == 0) * add_to_first);
  }
  if (is_symmetric) {
    sparse_matrix<ld> b(n);
    for (auto[i, j, x] : a.get_data()) {
      b.set(i, j, b.get(i, j) + x / 2);
      b.set(j, i, b.get(j, i) + x / 2);
    }
    a = b;
  }
  return a;
}

std::tuple<sparse_matrix<ld>, std::vector<ld>, std::vector<ld>> gen(int n,
                                                                    int diag,
                                                                    ld add_to_first = 1,
                                                                    bool is_symmetric = false) {
  sparse_matrix<ld> a = gen_sparse(n, diag, add_to_first, is_symmetric);
  std::vector<ld> ans(n);
  std::uniform_real_distribution<ld> distribution(-1, 1);
  while (magnitude(ans) < 1e-8) {
    for (ld &x : ans) {
      x = distribution(rnd);
    }
  }
  std::vector<ld> b = mul(a, ans);
  return {a, ans, b};
}

full_matrix<ld> gen_full(int n, int diag, ld add_to_first = 1, bool is_symmetric = false) {
  full_matrix<ld> a(n, n);
  for (int i = 0; i < n; i++) {
    ld sum = 0;
    for (int j = std::max(0, i - diag); j <= std::min(i + diag, n - 1); j++) {
      if (i != j) {
        ld x = -(int) (rnd() % 5);
        a.set(i, j, x);
        sum -= x;
      }
    }
    a.set(i, i, sum + (i == 0) * add_to_first);
  }
  if (is_symmetric) {
    full_matrix<ld> b(n, n);
    for (uint32_t i = 0; i < n; i++) {
      for (uint32_t j = 0; j < i; j++) {
        ld x = a.get(i, j);
        b.set(i, j, x / 2);
        b.set(j, i, x / 2);
      }
    }
    a = b;
  }
  return a;
}

std::tuple<full_matrix<ld>, std::vector<ld>, std::vector<ld>> genFull(int n,
                                                                      int diag,
                                                                      ld add_to_first = 1,
                                                                      bool is_symmetric = false) {
  full_matrix<ld> a = gen_full(n, diag, add_to_first, is_symmetric);
  std::vector<ld> ans(n);
  std::uniform_real_distribution<ld> distribution(-1, 1);
  while (magnitude(ans) < 1e-8) {
    for (ld &x : ans) {
      x = distribution(rnd);
    }
  }
  std::vector<ld> b = mul(a, ans);
  return {a, ans, b};
}

std::tuple<full_matrix<ld>, std::vector<ld>, std::vector<ld>> genHilbert(uint32_t n) {
  full_matrix<ld> A(n, n);
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < n; j++) {
      A.set(i, j, 1.0 / (i + j + 1));
    }
  }
  std::vector<ld> ans(n);
  std::uniform_real_distribution<ld> distribution(-1, 1);
  for (uint32_t i = 0; i < n; i++) {
    ans[i] = (i + 1);
  }
//  while (magnitude(ans) < 1e-4) {
//    for (auto& x : ans) {
//      x = distribution(rnd);
//    }
//  }
  std::vector<ld> b = mul(A, ans);
  return {A, ans, b};
}

std::pair<sparse_matrix<ld>, std::vector<ld>> gen_tricky(int n,
                                                         int diag,
                                                         ld add_to_first = 1,
                                                         bool is_symmetric = false) {
  auto[A, f, b] = gen(n, diag, add_to_first, is_symmetric);
  return {A, b};
}

int nextInt(int l, int r) {
  return std::uniform_int_distribution<int>(l, r)(rnd);
}

ld nextLd(ld l, ld r) {
  return std::uniform_real_distribution<ld>(l, r)(rnd);
}

std::vector<std::vector<ld>> generate_matrix(int h, int w) {
  std::vector<std::vector<ld>> data(h, std::vector<ld>(w));
  for (auto &i : data) {
    for (long double &j : i) {
      j = nextLd(-10, 10);
    }
  }
  if (h == w) {
    for (uint32_t i = 0; i < h; i++) {
      for (uint32_t j = 0; j < i; j++) {
        ld sum = (data[i][j] + data[j][i]) / 2;
        data[i][j] = data[j][i] = sum;
      }
    }
  }
  return data;
}

std::vector<std::vector<ld>> generate_matrix(int h = -1) {
  if (h == -1) {
    h = nextInt(1, 10);
  }
  return generate_matrix(h, h);
}

#endif //SOLE_SOLVER_GENERATORS_H
