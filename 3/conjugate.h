//
// Created by stepavly on 11.05.2021.
//

#ifndef SOLE_SOLVER__CONJUGATE_H_
#define SOLE_SOLVER__CONJUGATE_H_

#include "sparse_matrix.h"

template<typename T>
std::vector<T> conjugate(const sparse_matrix<T>& A, const std::vector<T>& f, T eps = 1e-7l) {
  std::vector<T> x = f;
  std::vector<T> r = sub(f, mul(A, x));
  std::vector<T> z = r;
  while (magnitude(r) / magnitude(f) >= eps) {
    T r_dot = dot(r, r);
    T ak = r_dot / dot(mul(A, z), z);
    x = add(x, mul(ak, z));
    auto r1 = sub(r, mul(ak, mul(A, z)));
    T bk = dot(r1, r1) / r_dot;
    z = add(r1, mul(bk, z));
    r = r1;
  }
  return x;
}

#endif //SOLE_SOLVER__CONJUGATE_H_
