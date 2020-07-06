//
// Created by covariance on 06.07.2020.
//

#ifndef BIGINT_SHARED_VECTOR_WRAPPER_H
#define BIGINT_SHARED_VECTOR_WRAPPER_H
#pragma once

#include <vector>
#include <cstdint>
#include <string>

struct shared_vector_wrapper {
// region fields
  size_t counter;
  std::vector<uint32_t> data;
// endregion

// region constructors
  shared_vector_wrapper(size_t, uint32_t);
  shared_vector_wrapper(size_t);
// endregion

  size_t size() const;

  void resize(size_t);
  void resize(size_t, uint32_t);

  uint32_t back() const;

  void pop_back();
  void push_back(uint32_t);
};


#endif //BIGINT_SHARED_VECTOR_WRAPPER_H
