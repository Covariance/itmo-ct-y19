//
// Created by covariance on 07.07.2020.
//

#ifndef BIGINT_SMALL_OBJECT_H
#define BIGINT_SMALL_OBJECT_H
#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>
#include "cow_wrapper.h"

class small_object {
// region fields
  cow_wrapper* data;
// endregion

  void uniquify() {
    if (!data->unique()) {
      data = data->extract_unique();
    }
  }

public:
  // region (cons/des)tructors
  small_object(size_t size, uint32_t val) {
    data = new cow_wrapper(std::vector<uint32_t>(size, val));
  }

  small_object(const small_object& that) {
    that.data->add_ref();
    data = that.data;
  }

  ~small_object() {
    if (data->unique()) {
      delete data;
      data = nullptr;
    } else {
      data->rem_ref();
    }
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

  bool operator==(const small_object& that) const {
    return *this->data == *that.data;
  }
  // endregion

  // region changers
  small_object& operator=(const small_object& that) {
    if (this != &that) {
      if (data->unique()) {
        delete data;
      } else {
        data->rem_ref();
      }
      that.data->add_ref();
      data = that.data;
    }
    return *this;
  }

  void resize(size_t size, uint32_t val) {
    uniquify();
    data->resize(size, val);
  }

  uint32_t& operator[](size_t i) {
    uniquify();
    return (*data)[i];
  }

  void pop_back() {
    uniquify();
    data->pop_back();
  }

  void push_back(uint32_t val) {
    uniquify();
    data->push_back(val);
  }

  void reverse() {
    uniquify();
    data->reverse();
  }

  void insert(size_t len) {
    data->insert(len);
    //data->insert(data->begin(), len, 0);
  }

  void erase(size_t len) {
    uniquify();
    data->erase(len);
  }
  // endregion
};

#endif //BIGINT_SMALL_OBJECT_H
