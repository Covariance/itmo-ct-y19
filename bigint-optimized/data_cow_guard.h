//
// Created by covariance on 07.07.2020.
//

#ifndef BIGINT_DATA_COW_GUARD_H
#define BIGINT_DATA_COW_GUARD_H
#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

class data_cow_guard {
  std::vector<uint32_t>* data;

  // region inners

  // endregion
public:
  // region (cons/des)tructors
  data_cow_guard(size_t size, uint32_t val) {
    data = new std::vector<uint32_t>(size, val);
  }

  data_cow_guard(const data_cow_guard& that) {
    data = new std::vector<uint32_t>(*that.data);
  }

  ~data_cow_guard() {
    delete data;
    data = nullptr;
  }
  // endregion

  // region accessors
  size_t size() const {
    return data->size();
  }

  uint32_t operator[](size_t i) const {
    return (*data)[i];
  }

  uint32_t back() const {
    return data->back();
  }

  bool operator==(const data_cow_guard& that) const {
    return *(this->data) == *that.data;
  }
  // endregion

  // region changers
  data_cow_guard& operator=(const data_cow_guard& that) {
    if (this != &that) {
      delete this->data;
      this->data = new std::vector<uint32_t>(*that.data);
    }
    return *this;
  }

  void resize(size_t size, uint32_t val) {
    data->resize(size, val);
  }

  uint32_t& operator[](size_t i) {
    return (*data)[i];
  }

  void pop_back() {
    data->pop_back();
  }

  void push_back(uint32_t val) {
    data->push_back(val);
  }

  void reverse() {
    std::reverse(data->begin(), data->end());
  }

  void insert(size_t len) {
    data->insert(data->begin(), len, 0);
  }

  void erase(size_t len) {
    data->erase(data->begin(), data->begin() + len);
  }
  // endregion
};

#endif //BIGINT_DATA_COW_GUARD_H
