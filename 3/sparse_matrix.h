//
// Created by stepavly on 10.05.2021.
//

#ifndef SOLE_SOLVER__SPARSE_MATRIX_H_
#define SOLE_SOLVER__SPARSE_MATRIX_H_

#include <unordered_map>
#include <fstream>
#include "matrix.h"

template<typename T>
class sparse_matrix : public matrix<T> {
  struct element_view {
   private:
    uint32_t i, j;

   public:
    element_view(std::initializer_list<uint32_t> list)
      : i(*list.begin()), j(*std::next(list.begin())) {}

    element_view(uint32_t i, uint32_t j)
      : i(i), j(j) {}

    size_t operator()(const element_view &other) const {
      return other.i * 1'000'000 + other.j;
    }

    [[nodiscard]] std::pair<uint32_t, uint32_t> as_pair() const {
      return {i, j};
    }

    bool operator==(const element_view &rhs) const {
      return i == rhs.i && j == rhs.j;
    }

    bool operator!=(const element_view &rhs) const {
      return !(rhs == *this);
    }
  };

  struct element_view_hash {
    std::size_t operator()(const element_view &other) const {
      auto[i, j] = other.as_pair();
      return i * 1'000'000 + j;
    }
  };

  mutable std::unordered_map<element_view, T, element_view_hash> data;
  std::unordered_map<uint32_t, std::unordered_map<uint32_t, T>> data_by_column;
  uint32_t size;
 public:

  explicit sparse_matrix(uint32_t size)
    : size(size) {}

  void set(uint32_t i, uint32_t j, T value) override {
    data[{i, j}] = value;
    data_by_column[i][j] = value;
  }

  T get(uint32_t i, uint32_t j) const override {
    auto iterator = data.find({i, j});
    return iterator == data.end() ? T() : iterator->second;
  }

  [[nodiscard]] uint32_t xSize() const override {
    return size;
  }

  [[nodiscard]] uint32_t ySize() const override {
    return size;
  }

  std::vector<std::tuple<uint32_t, uint32_t, T>> get_data() const {
    std::vector<std::tuple<uint32_t, uint32_t, T>> vector_data(data.size());
    auto it = vector_data.begin();
    for (const auto&[view, x] : data) {
      auto[i, j] = view.as_pair();
      *it = std::tie(i, j, x);
      ++it;
    }
    return vector_data;
  }

  std::vector<std::tuple<uint32_t, uint32_t, T>> get_row(uint32_t row) const {
    auto column_data_ptr = data_by_column.find(row);
    if (column_data_ptr == data_by_column.end()) {
      return {};
    }
    std::vector<std::tuple<uint32_t, uint32_t, T>> vector_data(column_data_ptr->second.size());
    auto it = vector_data.begin();
    for (const auto&[column, x] : column_data_ptr->second) {
      *it = std::tie(row, column, x);
      ++it;
    }
    return vector_data;
  }

  void save(const std::string &file) override {
    std::ofstream out;
    out.open(file);

    auto _data = get_data();

    out << _data.size() << std::endl;

    for (auto entry : _data) {
      out << std::get<0>(entry) << ' ' << std::get<1>(entry) << ' ' << std::get<2>(entry) << std::endl;
    }

    out.close();
  }

  void load(const std::string &file) override {
    std::ifstream in;
    in.open(file);

    uint32_t sz;
    in >> sz;

    data.clear();
    while (sz--) {
      uint32_t row, column;
      T val;
      in >> row >> column >> val;
      data[{row, column}] = val;
    }

    in.close();
  }
};

template<typename T>
sparse_matrix<T> mul(const sparse_matrix<T> &lhs, const sparse_matrix<T> &rhs) {
  sparse_matrix<T> res(lhs.xSize());
  for (auto[i, k, x] : lhs.get_data()) {
    for (auto[_k, j, y] : rhs.get_row(k)) {
      res.set(i, j, res.get(i, j) + x * y);
    }
  }
  return res;
}

template<typename T>
std::vector<T> mul(const sparse_matrix<T> &lhs, const std::vector<T> &rhs) {
  std::vector<T> res(rhs.size());
  for (auto[i, j, x] : lhs.get_data()) {
    res[i] += x * rhs[j];
  }
  return res;
}

template<typename T>
std::vector<T> mul(const std::vector<T> &lhs, const sparse_matrix<T> &rhs) {
  std::vector<T> res(lhs.size());
  for (auto[i, j, x] : rhs.get_data()) {
    res[j] += x * lhs[i];
  }
  return res;
}

template<typename T>
sparse_matrix<T> add(const sparse_matrix<T> &lhs, const sparse_matrix<T> &rhs) {
  sparse_matrix<T> res(lhs.xSize(), lhs.ySize());
  for (auto[i, j, x] : lhs.get_data()) {
    res.set(i, j, x);
  }
  for (auto[i, j, x] : rhs.get_data()) {
    res.set(i, j, res.get(i, j) + x);
  }
  return res;
}

template<typename T>
sparse_matrix<T> sub(const sparse_matrix<T> &lhs, const sparse_matrix<T> &rhs) {
  sparse_matrix<T> res(lhs.xSize(), lhs.ySize());
  for (auto[i, j, x] : lhs.get_data()) {
    res.set(i, j, x);
  }
  for (auto[i, j, x] : rhs.get_data()) {
    res.set(i, j, res.get(i, j) - x);
  }
  return res;
}

#endif //SOLE_SOLVER__SPARSE_MATRIX_H_
