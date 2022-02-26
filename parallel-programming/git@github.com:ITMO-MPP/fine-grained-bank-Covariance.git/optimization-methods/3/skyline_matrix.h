//
// Created by covariance on 10.05.2021.
//

#ifndef SOLE_SOLVER__SKYLINE_MATRIX_H_
#define SOLE_SOLVER__SKYLINE_MATRIX_H_

/*
 * Matrix is in skyline view, u is upper skyline, l is leftwards skyline,
 * contracts: u.size() == l.size(), u[i].size() == l[i].size() + 1
 */
template<typename T>
class skyline_matrix : public matrix<T> {
  std::vector<std::vector<T>> u;
  std::vector<std::vector<T>> l;

 public:
  explicit skyline_matrix(std::vector<std::vector<T>> u, std::vector<std::vector<T>> l)
      : u(std::move(u)), l(std::move(l)) {}

  [[nodiscard]] virtual uint32_t xSize() const {
    return u.size();
  }

  [[nodiscard]] virtual uint32_t ySize() const {
    return u.size();
  }

  virtual T get(uint32_t i, uint32_t j) const {
    if (i <= j) {
      if (j - i >= u[j].size()) {
        return 0;
      } else {
        return u[j][j - i];
      }
    } else {
      if (i - j - 1 >= l[i].size()) {
        return 0;
      } else {
        return l[i][i - j - 1];
      }
    }
  }

  virtual void set(uint32_t i, uint32_t j, T value) {
    if (value == 0) {
      return;
    }
    if (i <= j) {
      u[j][j - i] = value;
    } else {
      l[i][i - j - 1] = value;
    }
  }

  virtual void save(const std::string &file) {}
  virtual void load(const std::string &file) {}
};

#endif //SOLE_SOLVER__SKYLINE_MATRIX_H_
