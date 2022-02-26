//
// Created by covariance on 09.05.2021.
//

#ifndef SOLE_SOLVER__FULL_MATRIX_H_
#define SOLE_SOLVER__FULL_MATRIX_H_

#include <cstdint>
#include <fstream>
#include "matrix.h"

template<typename T>
class full_matrix : public matrix<T> {
  std::vector<std::vector<T>> data;

 public:
  explicit full_matrix(uint32_t size) : data(size, std::vector<T>(size, 0)) {}

  explicit full_matrix(uint32_t size1, uint32_t size2) : data(size1, std::vector<T>(size2, 0)) {}

  explicit full_matrix(std::vector<std::vector<T>> data) : data(std::move(data)) {}

  [[nodiscard]] virtual uint32_t xSize() const {
    return data.size();
  }

  [[nodiscard]] virtual uint32_t ySize() const {
    return data[0].size();
  }

  virtual T get(uint32_t i, uint32_t j) const {
    return data[i][j];
  }

  virtual void set(uint32_t i, uint32_t j, T value) {
    data[i][j] = value;
  }

  virtual void save(const std::string &file) {
    std::ofstream out;
    out.open(file);

    out << xSize() << ySize() << std::endl;
    for (auto row : data) {
      for (auto i : row) {
        out << i << ' ';
      }
      out << std::endl;
    }
    out << std::endl;

    out.close();
  }

  virtual void load(const std::string &file) {
    std::ifstream in;
    in.open(file);

    uint32_t xsz, ysz;
    in >> xsz >> ysz;
    data.assign(xsz, std::vector<T>(ysz));
    for (auto &row : data) {
      for (auto &i : row) {
        in >> i;
      }
    }

    in.close();
  }
};

template<typename T>
full_matrix<T> mul(const matrix<T> &lhs, const matrix<T> &rhs) {
  uint32_t n = lhs.xSize(), m = rhs.xSize(), l = rhs.ySize();
  std::vector<std::vector<T>> result(n, std::vector<T>(l, 0));

  for (uint32_t i = 0; i != n; ++i) {
    for (uint32_t j = 0; j != l; ++j) {
      for (uint32_t k = 0; k != m; ++k) {
        result[i][j] += lhs.get(i, k) * rhs.get(k, j);
      }
    }
  }

  return full_matrix<T>(result);
}

template<typename T>
std::vector<T> mul(const matrix<T> &lhs, const std::vector<T> &rhs) {
  full_matrix<T> temp(rhs.size(), 1);
  for (uint32_t i = 0; i < rhs.size(); i++) {
    temp.set(i, 0, rhs[i]);
  }
  auto t_res = mul(lhs, temp);
  std::vector<T> res(rhs.size());
  for (uint32_t i = 0; i < rhs.size(); i++) {
    res[i] = t_res.get(i, 0);
  }
  return res;
}

#endif //SOLE_SOLVER__FULL_MATRIX_H_
