//
// Created by covariance on 10.05.2021.
//

#ifndef SOLE_SOLVER__SOLE_SOLVER_LU_H_
#define SOLE_SOLVER__SOLE_SOLVER_LU_H_

std::vector<long double> solve(const matrix<long double> &l,
                               const matrix<long double> &u,
                               std::vector<long double> b) {
  std::vector<long double> y(b.size(), 0);
  for (uint32_t i = 0; i != b.size(); ++i) {
    y[i] = b[i] / l.get(i, i);

    for (uint32_t j = i; j != b.size(); ++j) {
      b[j] -= y[i] * l.get(j, i);
    }
  }

  std::vector<long double> x(y.size(), 0);
  for (uint32_t i = y.size(); i != 0; --i) {
    x[i - 1] = y[i - 1] / u.get(i - 1, i - 1);

    for (uint32_t j = 0; j != i; ++j) {
      y[j] -= x[i - 1] * u.get(j, i - 1);
    }
  }

  return x;
}

std::vector<long double> solve(const matrix<long double> &combined_lu, std::vector<long double> b) {
  std::vector<long double> y(b.size(), 0);
  for (uint32_t i = 0; i != b.size(); ++i) {
    y[i] = b[i] / combined_lu.get(i, i);

    for (uint32_t j = i; j != b.size(); ++j) {
      b[j] -= y[i] * combined_lu.get(j, i);
    }
  }

  std::vector<long double> x(y.size(), 0);
  for (uint32_t i = y.size(); i != 0; --i) {
    x[i - 1] = y[i - 1];

    for (uint32_t j = 0; j != i; ++j) {
      y[j] -= x[i - 1] * combined_lu.get(j, i - 1);
    }
  }

  return x;
}

#endif //SOLE_SOLVER__SOLE_SOLVER_LU_H_
