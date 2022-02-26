//
// Created by covariance on 09.05.2021.
//

#ifndef SOLE_SOLVER__LU_DECOMPOSITION_H_
#define SOLE_SOLVER__LU_DECOMPOSITION_H_

#include <matrix.h>
#include <left_triangle_matrix.h>
#include <right_triangle_matrix.h>

std::pair<left_triangle_matrix<long double>,
          right_triangle_matrix<long double>> LUDecomposition(const matrix<long double> &a) {
  uint32_t n = a.xSize();

  auto l = left_triangle_matrix<long double>(n);
  auto u = right_triangle_matrix<long double>(n);

  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = i; j < n; j++) {
      long double sm = 0.;
      for (k = 0; k < i; k++) {
        sm += l.get(j, k) * u.get(k, i);
      }
      if (a.get(j, i) != sm) {
        l.set(j, i, a.get(j, i) - sm);
      }
    }
    for (j = i; j < n; j++) {
      if (j == i)
        u.set(i, j, 1);
      else {
        long double sm = 0.;
        for (k = 0; k < i; k++) {
         sm += l.get(i, k) * u.get(k, j);
        }
        if (a.get(i, j) != sm) {
          u.set(i, j, (a.get(i, j) - sm) / l.get(i, i));
        }
      }
    }
  }

  return std::make_pair(l, u);
}

#endif //SOLE_SOLVER__LU_DECOMPOSITION_H_
