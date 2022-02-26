//
// Created by stepavly on 10.05.2021.
//

#include <random>
#include <iostream>
#include "sparse_matrix.h"
#include "full_matrix.h"
#include "generators.h"
#include "conjugate.h"
#include "gauss.h"
using namespace std;

using ld = long double;

sparse_matrix<ld> construct(const vector<vector<ld>> &data) {
  sparse_matrix<ld> res(data.size());
  for (uint32_t i = 0; i < data.size(); i++) {
    for (uint32_t j = 0; j < data[i].size(); j++) {
      res.set(i, j, data[i][j]);
    }
  }
  return res;
}

vector<ld> constructVector(const vector<vector<ld>> &data) {
  vector<ld> res(data.size());
  for (uint32_t i = 0; i < res.size(); i++) {
    res[i] = data[i][0];
  }
  return res;
}

void test01_multiply() {
  for (int times = 0; times < 100; times++) {
    auto vvA = generate_matrix();
    auto vvB = generate_matrix(vvA[0].size());
    const matrix<ld> &found = mul(construct(vvA), construct(vvB));
    const matrix<ld> &expected = mul(full_matrix(vvA), full_matrix(vvB));
    if (found != expected) {
      cerr << "test01_multiply: not passed" << endl;
      return;
    }
  }
  cerr << "test01_multiply: OK" << endl;
}

void test02_rhs_vector_multiply() {
  for (int times = 0; times < 100; times++) {
    auto vvA = generate_matrix();
    auto vvB = generate_matrix(vvA.size(), 1);
    vector<ld> found = mul(construct(vvA), constructVector(vvB));
    const matrix<ld> &expected = mul(full_matrix(vvA), full_matrix(vvB));
    for (uint32_t i = 0; i < found.size(); i++) {
      if (abs(found[i] - expected.get(i, 0)) > 1e-6l) {
        cerr << "test02_rhs_vector_multiply: not passed" << endl;
        cerr << "Test #" << (times + 1) << ": " << (i + 1) << "-th coordinate differs by "
             << abs(found[i] - expected.get(i, 0)) << endl;
        return;
      }
    }
  }
  cerr << "test02_rhs_vector_multiply: OK" << endl;
}

void test03_lhs_vector_multiply() {
  for (int times = 0; times < 10; times++) {
    std::vector<std::vector<ld>> vvA = generate_matrix();
    std::vector<std::vector<ld>> vvB = generate_matrix(1, vvA[0].size());
    vector<long double> found = mul(vvB[0], construct(vvA));
    const matrix<ld> &expected = mul(full_matrix(vvB), full_matrix(vvA));
    for (uint32_t i = 0; i < found.size(); i++) {
      if (abs(found[i] - expected.get(0, i)) > 1e-6l) {
        cerr << "test03_lhs_vector_multiply: not passed" << endl;
        cerr << "Test #" << (times + 1) << ": " << (i + 1) << "-th coordinate differs by "
             << abs(found[i] - expected.get(i, 0)) << endl;
        return;
      }
    }
  }
  cerr << "test03_lhs_vector_multiply: OK" << endl;
}

void test04_conjugate() {
  for (int times = 0; times < 100; times++) {
    int n = nextInt(1, 100);
    auto[A, r] = gen_tricky(n, nextInt(1, n), 2, true);
    auto found = conjugate(A, r);
    std::vector<ld> expected(n);
    gauss(A, r, expected);
    ld error_found = magnitude(sub(mul(A, found), r));
    ld error_expected = magnitude(sub(mul(A, found), r));
    if (error_expected > 1e-6l) {
      if (error_found < 1e-6l) {
        cerr << "test03_lhs_vector_multiply: main solution is not correct" << endl;
        return;
      }
      continue;
    }
    if (error_found > 1e-6l) {
      cerr << "test03_lhs_vector_multiply: not passed" << endl;
      return;
    }
  }
  cerr << "test04_conjugate: OK" << endl;
}

int main() {
  test01_multiply();
  test02_rhs_vector_multiply();
  test03_lhs_vector_multiply();
  test04_conjugate();
}