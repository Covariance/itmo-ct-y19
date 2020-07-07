//
// Created by covariance on 07.05.2020.
//
#include "big_integer.h"

// region inners
namespace big_integer_inner {
  static const big_integer ZERO(0), ONE(1), TEN(10);
}

big_integer big_integer::convert(size_t blocks) const {
  big_integer result(*this);
  if (result.negative) {
    ++result;
    for (size_t i = 0; i != result.data.size(); ++i) { result.data[i] = ~result.data[i]; }
    result.data.resize(blocks, UINT32_MAX);
  } else {
    result.data.resize(blocks, 0);
  }
  return result;
}

big_integer bitwise(const big_integer& a, const big_integer& b,
                    const std::function<uint32_t(uint32_t, uint32_t)>& op) {
  size_t sz = std::max(a.data.size(), b.data.size()) + 1;
  big_integer result, tma = a.convert(sz), tmb = b.convert(sz);
  result.data.resize(sz, 0);
  for (size_t i = 0; i < sz; ++i) {
    result.data[i] = op(tma.data[i], tmb.data[i]);
  }
  result.negative = op(tma.negative, tmb.negative);
  result.normalize();
  if (result.negative) {
    for (size_t i = 0; i != result.data.size(); ++i) { result.data[i] = ~result.data[i]; }
    --result;
  }
  result.normalize();
  return result;
}

inline void big_integer::normalize() {
  while (data.size() > 1 && data.back() == 0) { data.pop_back(); }
  if (this->data.size() == 1 && this->data[0] == 0) { negative = false; }
}
// endregion

// region constructors
big_integer::big_integer()
  : data(1, 0)
  , negative(false) {}

big_integer::big_integer(int x)
  : data(1, static_cast<uint32_t>(std::abs(static_cast<int64_t>(x))))
  , negative(x < 0) {}

big_integer::big_integer(uint32_t x)
  : data(1, x)
  , negative(false) {}

big_integer::big_integer(uint64_t x)
  : data(2, 0)
  , negative(false) {
  data[0] = static_cast<uint32_t>(x & (UINT32_MAX));
  data[1] = static_cast<uint32_t>(x >> 32u);
}

big_integer::big_integer(const std::string& s)
  : data(1, 0)
  , negative(false) {
  size_t i = (s.length() > 0 && (s[0] == '-' || s[0] == '+')) ? 0 : -1;
  while (++i < s.length()) { *this = (*this * big_integer_inner::TEN) + (s[i] - '0'); }
  negative = (s[0] == '-');
  normalize();
}
// endregion

// region support functions
void big_integer::swap(big_integer& other) {
  std::swap(data, other.data);
  std::swap(negative, other.negative);
}

std::string to_string(const big_integer& a) {
  if (a == big_integer_inner::ZERO) { return "0"; }

  std::string ans;
  big_integer tmp(a), cycle_tmp;

  while (tmp != big_integer_inner::ZERO) {
    cycle_tmp = tmp / big_integer_inner::TEN;
    ans += char('0' + (tmp - cycle_tmp * big_integer_inner::TEN).data[0]);
    tmp = cycle_tmp;
  }
  if (a.negative) { ans += '-'; }
  reverse(ans.begin(), ans.end());
  return ans;
}
// endregion

// region unary operators
big_integer big_integer::operator+() const {
  return big_integer(*this);
}

big_integer big_integer::operator-() const {
  big_integer tmp(*this);
  tmp.negative = !tmp.negative;
  tmp.normalize();
  return tmp;
}

big_integer big_integer::operator~() const {
  return -(*this) - big_integer_inner::ONE;
}
// endregion

// region (inc/dec)rements
big_integer& big_integer::operator++() {
  return (*this += big_integer_inner::ONE);
}

const big_integer big_integer::operator++(int) {
  const big_integer ret = *this;
  *this += big_integer_inner::ONE;
  return ret;
}

big_integer& big_integer::operator--() {
  return (*this -= big_integer_inner::ONE);
}

const big_integer big_integer::operator--(int) {
  const big_integer ret = *this;
  *this -= big_integer_inner::ONE;
  return ret;
}
// endregion

// region boolean operators
bool operator==(const big_integer& a, const big_integer& b) {
  if (a.negative != b.negative || a.data.size() != b.data.size()) { return false; }
  for (size_t i = 0; i != a.data.size(); ++i) {
    if (a.data[i] != b.data[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const big_integer& a, const big_integer& b) {
  return !(a == b);
}

bool operator<(const big_integer& a, const big_integer& b) {
  if (a.negative != b.negative) { return a.negative; }

  if (a.data.size() != b.data.size()) {
    return !a.negative ^ (a.data.size() > b.data.size());
  } else {
    for (size_t i = a.data.size(); i != 0; --i) {
      if (a.data[i - 1] != b.data[i - 1]) {
        return !a.negative ^ (a.data[i - 1] > b.data[i - 1]);
      }
    }
    return false;
  }
}

bool operator>(const big_integer& a, const big_integer& b) {
  return (b < a);
}

bool operator<=(const big_integer& a, const big_integer& b) {
  return !(a > b);
}

bool operator>=(const big_integer& a, const big_integer& b) {
  return !(a < b);
}
// endregion

// region usual binary operators
big_integer operator+(const big_integer& a, const big_integer& b) {
  if (a.negative != b.negative) {
    return (a.negative ? b - (-a) : a - (-b));
  }

  size_t size = std::max(a.data.size(), b.data.size());
  uint64_t sum, carry = 0;
  big_integer res;
  res.data.resize(size + 1, 0);
  for (size_t i = 0; i != size; ++i) {
    sum = carry;
    if (i < a.data.size()) { sum += a.data[i]; }
    if (i < b.data.size()) { sum += b.data[i]; }
    carry = (sum > UINT32_MAX ? 1 : 0);
    res.data[i] = static_cast<uint32_t>(sum & UINT32_MAX);
  }
  res.data[size] = static_cast<uint32_t>(carry);
  res.negative = a.negative;
  res.normalize();
  return res;
}

big_integer operator-(const big_integer& a, const big_integer& b) {
  if (a.negative != b.negative) {
    return (a.negative ? -((-a) + b) : a + (-b));
  }
  if (a.negative) { return (-b) - (-a); }
  if (a < b) { return -(b - a); }

  uint32_t sub, carry = 0;
  big_integer res;
  res.data.resize(a.data.size(), 0);

  for (size_t i = 0; i != a.data.size(); ++i) {
    if (i >= b.data.size()) {
      res.data[i] = (a.data[i] >= carry) ? a.data[i] - carry : UINT32_MAX;
      carry = (a.data[i] >= carry) ? 0 : 1;
    } else {
      if (a.data[i] >= b.data[i]) {
        sub = (a.data[i] - b.data[i] >= carry) ? a.data[i] - b.data[i] - carry : UINT32_MAX;
      } else {
        sub = UINT32_MAX - (b.data[i] - a.data[i]) + 1 - carry;
      }
      carry = a.data[i] >= b.data[i] ? ((a.data[i] - b.data[i] >= carry) ? 0 : 1) : 1;
      res.data[i] = sub;
    }
  }
  res.normalize();
  return res;
}

big_integer operator*(const big_integer& a, const big_integer& b) {
  if (a == big_integer_inner::ZERO || b == big_integer_inner::ZERO) { return big_integer(); }

  big_integer res;
  res.data.resize(a.data.size() + b.data.size(), 0);
  uint32_t carry;

  for (size_t i = 0; i != a.data.size(); ++i) {
    carry = 0;
    for (size_t j = 0; j != b.data.size(); ++j) {
      uint64_t mul = static_cast<uint64_t>(a.data[i]) * static_cast<uint64_t>(b.data[j]) +
                     static_cast<uint64_t>(res.data[i + j]) + static_cast<uint64_t>(carry);
      res.data[i + j] = static_cast<uint32_t>(mul & UINT32_MAX);
      carry = static_cast<uint32_t>(mul >> 32u);
    }
    res.data[i + b.data.size()] += carry;
  }
  res.negative = a.negative ^ b.negative;
  res.normalize();
  return res;
}

using uint128_t = unsigned __int128;

big_integer operator/(const big_integer& a, const big_integer& b) {
  big_integer divident = a, divisor = b;
  divident.negative = false;
  divisor.negative = false;
  if (divident < divisor) { return 0; }

  big_integer result;
  if (divisor.data.size() == 1) {
    uint64_t rest = 0, x;
    for (size_t i = 0; i != divident.data.size(); ++i) {
      x = (rest << 32u) | static_cast<uint64_t>(divident.data[divident.data.size() - 1 - i]);
      result.data.push_back(static_cast<uint32_t>(x / divisor.data[0]));
      rest = x % divisor.data[0];
    }
    result.data.reverse();
    result.normalize();

    result.negative = a.negative ^ b.negative;
    return result;
  }

  big_integer tmp_big;
  divident.negative = divisor.negative = false;
  uint32_t tmp_32;

  divident.data.push_back(0);

  size_t m = divisor.data.size() + 1, n = divident.data.size(), start;
  bool borrow;
  result.data.resize(n - m + 1, 0);
  union {
    int64_t sgn = 0;
    uint64_t uns;
  } c;


  for (size_t i = m - 1, j = result.data.size() - 1; i != n; ++i, --j) {
    c.sgn = 0;
    uint128_t x = (static_cast<uint128_t>(divident.data[divident.data.size() - 1]) << 64u) |
                  (static_cast<uint128_t>(divident.data[divident.data.size() - 2]) << 32u) |
                  (static_cast<uint128_t>(divident.data[divident.data.size() - 3]));
    uint128_t y = (static_cast<uint128_t>(divisor.data[divisor.data.size() - 1]) << 32u) |
                  (static_cast<uint128_t>(divisor.data[divisor.data.size() - 2]));

    tmp_32 = static_cast<uint32_t>(x / y);
    tmp_big = divisor * tmp_32;

    bool flag = true;
    for (size_t k = 1; k <= divident.data.size(); k++) {
      if (divident.data[divident.data.size() - k] !=
          (m - k < tmp_big.data.size() ? tmp_big.data[m - k] : 0)) {
        flag =
          divident.data[divident.data.size() - k] >
          (m - k < tmp_big.data.size() ? tmp_big.data[m - k] : 0);
        break;
      }
    }

    if (!flag) {
      tmp_32--;
      tmp_big -= divisor;
    }
    result.data[j] = tmp_32;

    start = divident.data.size() - m;
    borrow = false;
    for (size_t k = 0; k != m; ++k) {
      c.sgn = static_cast<int64_t>(divident.data[start + k])
              - static_cast<int64_t>(k < tmp_big.data.size() ? tmp_big.data[k] : 0)
              - static_cast<int64_t>(borrow);

      borrow = c.sgn < 0;
      c.uns &= UINT32_MAX;
      divident.data[start + k] = static_cast<uint32_t>(c.uns);
    }

    if (!divident.data.back()) { divident.data.pop_back(); }
  }

  result.negative = a.negative ^ b.negative;
  result.normalize();
  return result;
}

big_integer operator%(const big_integer& a, const big_integer& b) {
  return a - (a / b) * b;
}
// endregion

// region bitwise binary operators
big_integer operator&(const big_integer& a, const big_integer& b) {
  return bitwise(a, b, std::bit_and<uint32_t>());
}

big_integer operator|(const big_integer& a, const big_integer& b) {
  return bitwise(a, b, std::bit_or<uint32_t>());
}

big_integer operator^(const big_integer& a, const big_integer& b) {
  return bitwise(a, b, std::bit_xor<uint32_t>());
}

big_integer operator<<(const big_integer& a, int b) {
  big_integer result(a);
  size_t block_shift = static_cast<size_t>(b) >> 5u,
    inner_shift = static_cast<size_t>(b) & 31u;
  uint32_t carry = 0, tmp;
  for (size_t i = 0; i != result.data.size(); ++i) {
    tmp = (result.data[i] >> (32 - inner_shift));
    result.data[i] = ((result.data[i] << inner_shift) | carry);
    carry = tmp;
  }
  if (carry > 0) { result.data.push_back(carry); }
  result.data.insert_zeros_begin(block_shift);
  return result;
}

big_integer operator>>(const big_integer& a, int b) {
  big_integer result(a);
  size_t block_shift = static_cast<size_t> (b) >> 5u,
    inner_shift = static_cast<size_t> (b) & 31u;
  uint32_t carry = 0, tmp;
  result.data.erase_from_begin(block_shift);
  for (size_t i = result.data.size(); i != 0; --i) {
    tmp = (result.data[i - 1] << (32 - inner_shift));
    result.data[i - 1] = ((result.data[i - 1] >> inner_shift) | carry);
    carry = tmp;
  }
  result.normalize();
  if (result.negative) { result--; }
  return result;
}
// endregion

// region derived operators
big_integer& big_integer::operator=(const big_integer& that) {
  big_integer tmp(that);
  swap(tmp);
  return *this;
}

big_integer& big_integer::operator+=(const big_integer& rhs) {
  return *this = *this + rhs;
}

big_integer& big_integer::operator-=(const big_integer& rhs) {
  return *this = *this - rhs;
}

big_integer& big_integer::operator*=(const big_integer& rhs) {
  return *this = *this * rhs;
}

big_integer& big_integer::operator/=(const big_integer& rhs) {
  return *this = *this / rhs;
}

big_integer& big_integer::operator%=(const big_integer& rhs) {
  return *this = *this % rhs;
}

big_integer& big_integer::operator&=(const big_integer& rhs) {
  return *this = *this & rhs;
}

big_integer& big_integer::operator|=(const big_integer& rhs) {
  return *this = *this | rhs;
}

big_integer& big_integer::operator^=(const big_integer& rhs) {
  return *this = *this ^ rhs;
}

big_integer& big_integer::operator<<=(int rhs) {
  return *this = *this << rhs;
}

big_integer& big_integer::operator>>=(int rhs) {
  return *this = *this >> rhs;
}
// endregion

// region io operators
std::ostream& operator<<(std::ostream& s, const big_integer& a) {
  return s << to_string(a);
}

std::istream& operator>>(std::istream& in, big_integer& a) {
  std::string s;
  in >> s;
  a = big_integer(s);
  return in;
}
// endregion