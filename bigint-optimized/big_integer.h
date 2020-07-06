//
// Created by covariance on 07.05.2020.
//
#ifndef BIGINT_BIG_INTEGER_H
#define BIGINT_BIG_INTEGER_H
#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <functional>
#include "shared_vector_wrapper.h"

class big_integer {
// region fields
  std::vector<uint32_t> data;
  bool negative;
// endregion

// region inners
  size_t size() const;
  big_integer convert(size_t) const;
  friend big_integer bitwise(const big_integer& a, const big_integer& b,
                             const std::function<uint32_t(uint32_t, uint32_t)>& op);
  void normalize();
// endregion

public:
// region constructors
  big_integer();
  big_integer(int);
  big_integer(uint32_t);
  big_integer(uint64_t);
  explicit big_integer(std::string const&);
  big_integer(big_integer const&) = default;
// endregion

// region destructor
  ~big_integer() = default;
// endregion

// region support fucntions
  void swap(big_integer&);
  friend std::string to_string(big_integer const&);
// endregion

// region unary operators
  big_integer operator+() const;
  big_integer operator-() const;
  big_integer operator~() const;
// endregion

// region (inc/dec)rements
  big_integer& operator++();
  const big_integer operator++(int);
  big_integer& operator--();
  const big_integer operator--(int);
// endregion

// region boolean operators
  friend bool operator==(big_integer const& a, big_integer const& b);
  friend bool operator!=(big_integer const& a, big_integer const& b);
  friend bool operator<(big_integer const& a, big_integer const& b);
  friend bool operator>(big_integer const& a, big_integer const& b);
  friend bool operator<=(big_integer const& a, big_integer const& b);
  friend bool operator>=(big_integer const& a, big_integer const& b);
// endregion

// region usual binary operators
  friend big_integer operator+(const big_integer& a, big_integer const& b);
  friend big_integer operator-(const big_integer& a, big_integer const& b);
  friend big_integer operator*(const big_integer& a, big_integer const& b);
  friend big_integer operator/(const big_integer& a, big_integer const& b); // TODO
  friend big_integer operator%(const big_integer& a, big_integer const& b);
// endregion

// region bitwise binary operators
  friend big_integer operator&(const big_integer& a, big_integer const& b);
  friend big_integer operator|(const big_integer& a, big_integer const& b);
  friend big_integer operator^(const big_integer& a, big_integer const& b);
  friend big_integer operator<<(const big_integer& a, int b);
  friend big_integer operator>>(const big_integer& a, int b);
// endregion

// region derived operators
  big_integer& operator=(big_integer const&);
  big_integer& operator+=(big_integer const&);
  big_integer& operator-=(big_integer const&);
  big_integer& operator*=(big_integer const&);
  big_integer& operator/=(big_integer const&);
  big_integer& operator%=(big_integer const&);
  big_integer& operator&=(big_integer const&);
  big_integer& operator|=(big_integer const&);
  big_integer& operator^=(big_integer const&);
  big_integer& operator<<=(int);
  big_integer& operator>>=(int);
// endregion

// region io operators
  friend std::ostream& operator<<(std::ostream& out, big_integer const& a);
  friend std::istream& operator>>(std::istream& in, big_integer& a);
// endregion
};

#endif //BIGINT_BIG_INTEGER_H