//
// Created by covariance on 07.07.2020.
//

#ifndef BIGINT_SMALL_OBJECT_H
#define BIGINT_SMALL_OBJECT_H
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "cow_wrapper.h"

class small_object {
// region fields
  static constexpr size_t MAX_SIZE = 2;
  bool small;
  size_t small_size;
  union {
    uint32_t small_val[MAX_SIZE]{};
    cow_wrapper* data;
  };
// endregion

// region inners
  void uniquify() {
    if (!data->unique()) {
      data = data->extract_unique();
    }
  }

  void desmall() {
    if (small) {
      data = new cow_wrapper(std::vector<uint32_t>(small_val, small_val + small_size));
      small = false;
    }
  }
// endregion
public:
// region (cons/des)tructors
  small_object(size_t size, uint32_t val)
    : small(size <= MAX_SIZE)
    , small_size(size) {
    if (small) {
      std::fill(small_val, small_val + small_size, val);
    } else {
      data = new cow_wrapper(std::vector<uint32_t>(size, val));
    }
  }

  small_object(const small_object& that)
    : small(that.small)
    , small_size(that.small_size) {
    if (small) {
      std::copy_n(that.small_val, small_size, small_val);
    } else {
      that.data->add_ref();
      data = that.data;
    }
  }

  ~small_object() {
    if (!small) {
      if (data->unique()) {
        delete data;
        data = nullptr;
      } else {
        data->remove_ref();
      }
    }
  }
// endregion

// region accessors
  size_t size() const {
    return small ? small_size : data->size();
  }

  uint32_t operator[](size_t i) const {
    return small ? small_val[i] : (*data)[i];
  }

  uint32_t back() const {
    return small ? small_val[small_size - 1] : data->back();
  }
// endregion

// region changers
  small_object& operator=(const small_object& that) {
    if (this != &that) {
      if (this->small && that.small) {
        small_size = that.small_size;
        std::copy_n(that.small_val, small_size, small_val);
        return *this;
      }

      if (this->small && !that.small) {
        small = false;
        that.data->add_ref();
        data = that.data;
        return *this;
      }

      if (!this->small && that.small) {
        if (data->unique()) {
          delete data;
        } else {
          data->remove_ref();
        }
        small = that.small;
        small_size = that.small_size;
        std::copy_n(that.small_val, small_size, small_val);
        return *this;
      }

      if (!this->small && !that.small) {
        if (data->unique()) {
          delete data;
        } else {
          data->remove_ref();
        }
        that.data->add_ref();
        data = that.data;
        return *this;
      }
    }
    return *this;
  }

  void resize(size_t size, uint32_t val) {
#ifdef _GLIBCXX_DEBUG
    assert(small_size <= size);
#endif
    if (size > MAX_SIZE) {
      desmall();
    }
    if (small) {
      std::fill(small_val + small_size, small_val + size, val);
      small_size = size;
    } else {
      uniquify();
      data->resize(size, val);
    }
  }

  uint32_t& operator[](size_t i) {
    if (!small) { uniquify(); }
    return small ? small_val[i] : (*data)[i];
  }

  void pop_back() {
    if (small) {
      --small_size;
    } else {
      uniquify();
      data->pop_back();
    }
  }

  void push_back(uint32_t val) {
    if (small_size == MAX_SIZE) {
      desmall();
    }
    if (small) {
      small_val[small_size++] = val;
    } else {
      uniquify();
      data->push_back(val);
    }
  }

  void reverse() {
    if (small) {
      std::reverse(small_val, small_val + small_size);
    } else {
      uniquify();
      data->reverse();
    }
  }

  void insert_zeros_begin(size_t len) {
    if (len + small_size > MAX_SIZE) {
      desmall();
    }
    if (small) {
      std::move(small_val, small_val + small_size, small_val + len);
      std::fill(small_val, small_val + len, 0);
      small_size += len;
    } else {
      uniquify();
      data->insert(len);
    }
  }

  void erase_from_begin(size_t len) {
    if (small) {
      std::move(small_val + len, small_val + small_size, small_val);
    } else {
      uniquify();
      data->erase(len);
    }
  }
// endregion
};

#endif //BIGINT_SMALL_OBJECT_H
