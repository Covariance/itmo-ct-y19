//
// Created by covariance on 07.07.2020.
//

#ifndef BIGINT_COW_WRAPPER_H
#define BIGINT_COW_WRAPPER_H
#pragma once

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

class cow_wrapper {
// region fields
  size_t counter;
  std::vector<uint32_t> data;
// endregion
public:
// region COW functions
  bool unique() const {
    return counter == 1;
  }

  void add_ref() {
    ++counter;
  }

  void remove_ref() {
    --counter;
  }

  cow_wrapper* extract_unique() {
    if (unique()) { return this; }
    --counter;
    return new cow_wrapper(data);
  }
// endregion

// region (cons/des)tructors
  explicit cow_wrapper(std::vector<uint32_t> other_data)
    : counter(1)
    , data(std::move(other_data)) {}
// endregion

// region wrapped functions
  size_t size() const {
    return data.size();
  }

  uint32_t back() const {
    return data.back();
  }

  void pop_back() {
    data.pop_back();
  }

  void push_back(uint32_t val) {
    data.push_back(val);
  }

  void resize(size_t length, uint32_t val) {
    data.resize(length, val);
  }

  void reverse() {
    std::reverse(data.begin(), data.end());
  }

  void insert(size_t len) {
    data.insert(data.begin(), len, 0);
  }

  void erase(size_t len) {
    data.erase(data.begin(), data.begin() + len);
  }

  uint32_t operator[](size_t i) const {
    return data[i];
  }

  uint32_t& operator[](size_t i) {
    return data[i];
  }

  friend bool operator==(const cow_wrapper& a, const cow_wrapper& b) {
    return a.data == b.data;
  }
// endregion
};

#endif //BIGINT_COW_WRAPPER_H
