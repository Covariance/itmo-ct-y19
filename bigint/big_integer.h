//
// Created by covariance on 07.05.2020.
//
#ifndef BIGINT_BIG_INTEGER_H
#define BIGINT_BIG_INTEGER_H

#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <functional>

class big_integer {
  std::vector<uint32_t> data;
  bool negative;

  size_t size() const;
  void resize(size_t);
  big_integer convert(size_t) const;
  void normalize();
  bool zero() const;
  friend big_integer bitwise(big_integer& a, big_integer const& b,
                             const std::function<uint32_t(uint32_t, uint32_t)>& op);
  friend void difference(big_integer& a, big_integer const& b, size_t index);
  friend inline big_integer shortdiv(big_integer const& a, uint32_t b);

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

// region usual equal operators
  big_integer& operator=(big_integer const&);
  big_integer& operator+=(big_integer const&);
  big_integer& operator-=(big_integer const&);
  big_integer& operator*=(big_integer const&);
  big_integer& operator/=(big_integer const&);
  big_integer& operator%=(big_integer const&);
// endregion

// region bitwise equal operators
  big_integer& operator&=(big_integer const&);
  big_integer& operator|=(big_integer const&);
  big_integer& operator^=(big_integer const&);
  big_integer& operator<<=(int);
  big_integer& operator>>=(int);
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
  friend big_integer operator+(big_integer a, big_integer const& b);
  friend big_integer operator-(big_integer a, big_integer const& b);
  friend big_integer operator*(big_integer a, big_integer const& b);
  friend big_integer operator/(const big_integer& a, big_integer const& b); // TODO
  friend big_integer operator%(const big_integer& a, big_integer const& b);
// endregion

// region bitwise binary operators
  friend big_integer operator&(big_integer a, big_integer const& b);
  friend big_integer operator|(big_integer a, big_integer const& b);
  friend big_integer operator^(big_integer a, big_integer const& b);
  friend big_integer operator<<(big_integer a, int b);
  friend big_integer operator>>(big_integer a, int b);
// endregion

// region io operators
  friend std::ostream& operator<<(std::ostream& out, big_integer const& a);
  friend std::istream& operator>>(std::istream& in, big_integer& a);
// endregion
};
#endif //BIGINT_BIG_INTEGER_H