#ifndef SOLE_SOLVER__MATRIX_H_
#define SOLE_SOLVER__MATRIX_H_

#include <vector>
#include <cmath>
#include <ostream>

template<typename T>
class matrix;

template<typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m);

template<typename T>
class matrix {
 public:
  virtual ~matrix() = default;
  [[nodiscard]] virtual uint32_t xSize() const = 0;
  [[nodiscard]] virtual uint32_t ySize() const = 0;
  virtual T get(uint32_t, uint32_t) const = 0;
  virtual void set(uint32_t i, uint32_t j, T value) = 0;

  virtual void save(const std::string &file) = 0;
  virtual void load(const std::string &file) = 0;

  friend std::ostream &operator<<<>(std::ostream &out, const matrix &m);
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
  uint32_t xs = m.xSize();
  uint32_t ys = m.ySize();
  for (uint32_t i = 0; i != xs; ++i) {
    for (uint32_t j = 0; j != ys; ++j) {
      out << m.get(i, j) << ' ';
    }
    out << std::endl;
  }
  return out;
}

template<typename T>
bool operator==(const matrix<T> &a, const matrix<T> &b) {
  if (a.xSize() != b.xSize() || a.ySize() != b.ySize()) {
    return false;
  }
  for (uint32_t i = 0; i < a.xSize(); i++) {
    for (uint32_t j = 0; j < b.ySize(); j++) {
      if (std::abs(a.get(i, j) - b.get(i, j)) > 1e-6l) {
        return false;
      }
    }
  }
  return true;
}

template<typename T>
bool operator!=(const matrix<T> &a, const matrix<T> &b) {
  return !(a == b);
}

template<typename T>
std::vector<T> add(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  std::vector<T> res(lhs.size());
  for (uint32_t i = 0; i < rhs.size(); i++) {
    res[i] = lhs[i] + rhs[i];
  }
  return res;
}

template<typename T>
std::vector<T> sub(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  std::vector<T> res(lhs.size());
  for (uint32_t i = 0; i < rhs.size(); i++) {
    res[i] = lhs[i] - rhs[i];
  }
  return res;
}

template<typename T>
T dot(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  T res = 0;
  for (uint32_t i = 0; i < lhs.size(); i++) {
    res += lhs[i] * rhs[i];
  }
  return res;
}

template<typename T>
T magnitude(const std::vector<T> &x) {
  return std::sqrt(dot(x, x));
}

template<typename T>
std::vector<T> mul(const std::vector<T> &lhs, T rhs) {
  std::vector<T> res(lhs.size());
  for (uint32_t i = 0; i < lhs.size(); i++) {
    res[i] = lhs[i] * rhs;
  }
  return res;
}

template<typename T>
std::vector<T> mul(T lhs, const std::vector<T> &rhs) {
  return mul(rhs, lhs);
}

template<typename T>
std::vector<T> div(const std::vector<T> &lhs, T rhs) {
  std::vector<T> res(lhs.size());
  for (uint32_t i = 0; i < lhs.size(); i++) {
    res[i] = lhs[i] / rhs;
  }
  return res;
}

#endif //SOLE_SOLVER__MATRIX_H_
