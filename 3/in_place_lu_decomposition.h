//
// Created by covariance on 10.05.2021.
//

#ifndef SOLE_SOLVER__IN_PLACE_LU_DECOMPOSITION_H_
#define SOLE_SOLVER__IN_PLACE_LU_DECOMPOSITION_H_

void IPLUDecomposition(matrix<long double> &a) {
  uint32_t n = a.xSize();

  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = i; j < n; j++) {
      long double sm = 0.;
      for (k = 0; k < i; k++) {
        sm += a.get(j, k) * a.get(k, i);
      }
      a.set(j, i, a.get(j, i) - sm);
    }
    for (j = i + 1; j < n; j++) {
      long double sm = 0.;
      for (k = 0; k < i; k++) {
        sm += a.get(i, k) * a.get(k, j);
      }
      a.set(i, j, (a.get(i, j) - sm) / a.get(i, i));
    }
  }
}

#endif //SOLE_SOLVER__IN_PLACE_LU_DECOMPOSITION_H_
