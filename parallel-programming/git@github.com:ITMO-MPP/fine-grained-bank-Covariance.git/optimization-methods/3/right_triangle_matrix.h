//
// Created by covariance on 10.05.2021.
//

#ifndef SOLE_SOLVER__RIGHT_TRIANGLE_MATRIX_H_
#define SOLE_SOLVER__RIGHT_TRIANGLE_MATRIX_H_
template<typename T>
class right_triangle_matrix : public matrix<T> {
  std::vector<std::vector<T>> data;

 public:
  explicit right_triangle_matrix(uint32_t size) : data(size) {
    for (uint32_t i = 0; i != size; ++i) {
      data[i].assign(i + 1, 0);
    }
  }

  explicit right_triangle_matrix(std::vector<std::vector<T>> data) : data(std::move(data)) {}

  [[nodiscard]] virtual uint32_t xSize() const {
    return data.size();
  }

  [[nodiscard]] virtual uint32_t ySize() const {
    return data.size();
  }

  virtual T get(uint32_t i, uint32_t j) const {
    if (i > j) {
      return 0;
    }
    return data[j][i];
  }

  virtual void set(uint32_t i, uint32_t j, T value) {
    data[j][i] = value;
  }

  virtual void save(const std::string &file) {}
  virtual void load(const std::string &file) {}
};
#endif //SOLE_SOLVER__RIGHT_TRIANGLE_MATRIX_H_
