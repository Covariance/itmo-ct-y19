#ifndef SOLE_SOLVER_GAUSS_H
#define SOLE_SOLVER_GAUSS_H

#include "matrix.h"
#include <algorithm>
#include <iostream>
using namespace std;

long double EPS = 1e-9;

template<typename T>
int gauss(matrix<T> &a, std::vector<T> b, std::vector<T> &ans) {
  int n = (int) a.xSize();
  int m = (int) a.ySize();

  std::vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i) {
      if (abs(a.get(i, col)) > abs(a.get(sel, col))) {
        sel = i;
      }
    }
    if (std::abs(a.get(sel, col)) < EPS) {
      continue;
    }
    for (int i = col; i < m; ++i) {
      T tmp = a.get(sel, i);
      a.set(sel, i, a.get(row, i));
      a.set(row, i, tmp);
    }
    std::swap(b[sel], b[row]);
    where[col] = row;

    for (int i = 0; i < n; ++i) {
      if (i != row) {
        double c = a.get(i, col) / a.get(row, col);
        for (int j = col; j < m; ++j) {
          a.set(i, j, a.get(i, j) - a.get(row, j) * c);
        }
        b[i] -= b[row] * c;
      }
    }
    ++row;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; ++i) {
    if (where[i] != -1) {
      ans[i] = b[where[i]] / a.get(where[i], i);
    }
  }
  for (int i = 0; i < n; ++i) {
    ld sum = 0;
    for (int j = 0; j < m; ++j) {
      sum += ans[j] * a.get(i, j);
    }
    if (abs(sum - b[i]) > EPS) {
      return 0;
    }
  }

//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      cout << a.get(i, j) << " ";
//    }
//    cout << endl;
//  }

  for (int i = 0; i < m; ++i) {
    if (where[i] == -1) {
      return -1;
    }
  }
  return 1;
}

#endif //SOLE_SOLVER_GAUSS_H
