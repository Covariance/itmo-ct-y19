//
// Created by covariance on 13.05.2021.
//

#ifndef SOLE_SOLVER__PROFILE_MATRIX_H_
#define SOLE_SOLVER__PROFILE_MATRIX_H_

template<typename T>
class profile_matrix : public matrix<T> {
  uint32_t sz;
  std::vector<std::vector<T>> l, r;

 public:
  profile_matrix(uint32_t sz, std::vector<std::vector<T>> l, std::vector<std::vector<T>> r)
      : sz(sz), l(std::move(l)), r(std::move(r)) {}

  [[nodiscard]] virtual uint32_t xSize() const {
    return sz;
  }

  [[nodiscard]] virtual uint32_t ySize() const {
    return sz;
  }

  virtual T get(uint32_t i, uint32_t j) const {
    if (i <= j) {
      if (r[i].size() >= j - i + 1) {
        return r[i][j - i];
      }
      return 0;
    } else {
      if (l[i].size() >= i - j) {
        return l[i][i - j - 1];
      }
      return 0;
    }
  }

  virtual void set(uint32_t i, uint32_t j, T value) {
    if (value == 0) {
      return;
    }
    if (i <= j) {
      r[i][j - i] = value;
    } else {
      l[i][i - j - 1] = value;
    }
  }

  virtual void save(const std::string &file) {
    std::ofstream out;
    out.open(file);

    out << xSize() << std::endl;
    for (uint32_t i = 0; i != xSize(); ++i) {
      out << l[i].size() << ' ' << r[i].size() << std::endl;
      for (auto j : l[i]) {
        out << j << ' ';
      }
      out << std::endl;
      for (auto j : r[i]) {
        out << j << ' ';
      }
      out << std::endl;
    }

    out.close();
  }

  virtual void load(const std::string &file) {
    std::ifstream in;
    in.open(file);

    in >> sz;
    l.resize(sz);
    r.resize(sz);

    for (uint32_t i = 0; i != sz; ++i) {
      uint32_t lsz, rsz;
      in >> lsz >> rsz;
      l[i].resize(lsz);
      for (auto &j : l[i]) {
        in >> j;
      }
      r[i].resize(rsz);
      for (auto &j : r[i]) {
        in >> j;
      }
    }

    in.close();
  }
};

#endif //SOLE_SOLVER__PROFILE_MATRIX_H_
