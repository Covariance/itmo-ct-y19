//
// Created by covariance on 07.05.2020.
//

#include "big_integer.h"

// region inners
static const big_integer ZERO(0);
static const big_integer ONE(1);
static const big_integer TWO(2);
static const big_integer TEN(10);

size_t big_integer::size() const {
  return data.size();
}

void big_integer::resize(size_t blocks) {
  while (this->data.size() < blocks) { this->data.push_back(this->negative ? UINT32_MAX : 0); }
}

big_integer big_integer::convert(size_t blocks) const {
  big_integer result(*this);
  if (result.negative) {
    ++result;
    for (auto& block : result.data) { block = ~block; }
  }
  result.resize(blocks);
  return result;
}

big_integer bitwise(big_integer& a, big_integer const& b,
                    const std::function<uint32_t(uint32_t, uint32_t)>& op) {
  size_t sz = std::max(a.size(), b.size()) + 1;
  big_integer result, tma = a.convert(sz), tmb = b.convert(sz);
  result.resize(sz);
  for (size_t i = 0; i < sz; ++i) {
    result.data[i] = op(tma.data[i], tmb.data[i]);
  }
  result.negative = op(tma.negative, tmb.negative);
  result.normalize();
  if (result.negative) {
    for (auto& block : result.data) {
      block = ~block;
    }
    --result;
  }
  result.normalize();
  return result;
}

void big_integer::normalize() {
  while (size() > 1 && data.back() == 0) { data.pop_back(); }
  if (zero()) {
    negative = false;
  }
}

bool big_integer::zero() const {
  return (data.size() == 1 && data[0] == 0);
}
// endregion

// region constructors
big_integer::big_integer()
  : data(1)
  , negative(false) {}

big_integer::big_integer(int x)
  : data(1, (uint32_t) std::abs((int64_t) x))
  , negative(x < 0) {}

big_integer::big_integer(uint32_t x)
  : data(1, x)
  , negative(false) {}

big_integer::big_integer(uint64_t x)
  : data(0)
  , negative(false) {
  data.push_back((uint32_t) (x & (UINT32_MAX)));
  data.push_back((uint32_t) (x >> 32));
}

big_integer::big_integer(std::string const& s)
  : data(1, 0)
  , negative(false) {
  size_t i = (s.length() > 0 && (s[0] == '-' || s[0] == '+')) ? 0 : -1;
  while (++i < s.length()) { *this = (*this * TEN) + (s[i] - '0'); }
  negative = (s[0] == '-');
  normalize();
}
// endregion

// region support functions
void big_integer::swap(big_integer& other) {
  std::swap(data, other.data);
  std::swap(negative, other.negative);
}

std::string to_string(big_integer const& a) {
  if (a == big_integer()) { return "0"; }

  std::string ans;
  big_integer tmp(a);

  while (tmp != ZERO) {
    ans += char('0' + (tmp % TEN).data[0]);
    tmp /= TEN;
  }
  if (a.negative) { ans += '-'; }
  reverse(ans.begin(), ans.end());
  return ans;
}
// endregion

// region usual equal operators
big_integer& big_integer::operator=(big_integer const& one) {
  big_integer tmp(one);
  swap(tmp);
  return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs) {
  return *this = *this + rhs;
}

big_integer& big_integer::operator-=(big_integer const& rhs) {
  return *this = *this - rhs;
}

big_integer& big_integer::operator*=(big_integer const& rhs) {
  return *this = *this * rhs;
}

big_integer& big_integer::operator/=(big_integer const& rhs) {
  return *this = *this / rhs;
}

big_integer& big_integer::operator%=(big_integer const& rhs) {
  return *this = *this % rhs;
}
// endregion

// region bitwise equal operators
big_integer& big_integer::operator&=(big_integer const& rhs) {
  return *this = *this & rhs;
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
  return *this = *this | rhs;
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
  return *this = *this ^ rhs;
}

big_integer& big_integer::operator<<=(int rhs) {
  return *this = *this << rhs;
}

big_integer& big_integer::operator>>=(int rhs) {
  return *this = *this >> rhs;
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
  return -(*this) - ONE;
}
// endregion

// region (inc/dec)rements
big_integer& big_integer::operator++() {
  return (*this += ONE);
}

const big_integer big_integer::operator++(int) {
  const big_integer ret = *this;
  *this += 1;
  return ret;
}

big_integer& big_integer::operator--() {
  return (*this -= ONE);
}

const big_integer big_integer::operator--(int) {
  const big_integer ret = *this;
  *this -= 1;
  return ret;
}
// endregion

// region boolean operators
bool operator==(big_integer const& a, big_integer const& b) {
  return (a.negative == b.negative && a.data == b.data);
}

bool operator!=(big_integer const& a, big_integer const& b) {
  return !(a == b);
}

bool operator<(big_integer const& a, big_integer const& b) {
  if (a.negative != b.negative) { return a.negative; }

  if (a.negative) {
    if (a.size() != b.size()) {
      return a.size() > b.size();
    }
    size_t i = a.size();
    while (i--) {
      if (a.data[i] != b.data[i]) {
        return a.data[i] > b.data[i];
      }
    }
    return false;
  } else {
    if (a.size() != b.size()) {
      return a.size() < b.size();
    }
    size_t i = a.size();
    while (i--) {
      if (a.data[i] != b.data[i]) {
        return a.data[i] < b.data[i];
      }
    }
    return false;
  }
}

bool operator>(big_integer const& a, big_integer const& b) {
  return (b < a);
}

bool operator<=(big_integer const& a, big_integer const& b) {
  return !(a > b);
}

bool operator>=(big_integer const& a, big_integer const& b) {
  return !(a < b);
}
// endregion

// region usual binary operators
big_integer operator+(big_integer a, big_integer const& b) {
  if (a.negative != b.negative) {
    return (a.negative ? b - (-a) : a - (-b));
  }

  size_t size = std::max(a.size(), b.size());
  uint64_t sum = 0, carry = 0;
  big_integer res;
  res.data.resize(size + 1, 0);
  for (size_t i = 0; i < size; i++) {
    sum = carry;
    if (i < a.size()) { sum += a.data[i]; }
    if (i < b.size()) { sum += b.data[i]; }

    carry = (sum > UINT32_MAX ? 1 : 0);

    res.data[i] = (uint32_t) (sum & UINT32_MAX);
  }
  res.data[size] = (uint32_t) carry;
  res.negative = a.negative;
  res.normalize();
  return res;
}

big_integer operator-(big_integer a, big_integer const& b) {
  if (a.negative != b.negative) {
    return (a.negative ? -((-a) + b) : a + (-b));
  }
  if (a.negative) { return (-b) - (-a); }
  if (a < b) { return -(b - a); }
  uint32_t sub = 0, carry = 0;
  big_integer res;
  res.data.resize(a.size());

  for (size_t i = 0; i < a.size(); i++) {
    if (i >= b.size()) {
      if (a.data[i] >= carry) {
        res.data[i] = a.data[i] - carry;
        carry = 0;
      } else {
        res.data[i] = UINT32_MAX;
        carry = 1;
      }
      continue;
    }

    if (a.data[i] >= b.data[i]) {
      sub = a.data[i] - b.data[i];
      if (sub >= carry) {
        sub -= carry;
        carry = 0;
      } else {
        sub = UINT32_MAX;
        carry = 1;
      }
    } else {
      sub = UINT32_MAX - (b.data[i] - a.data[i]) + 1 - carry;
      carry = 1;
    }

    res.data[i] = sub;
  }
  res.normalize();
  return res;
}

big_integer operator*(big_integer a, big_integer const& b) {
  if (a == ZERO || b == ZERO) { return big_integer(); }

  big_integer res;
  res.data.resize(a.size() + b.size(), 0);

  for (size_t i = 0; i < a.size(); i++) {
    uint32_t carry = 0;
    for (size_t j = 0; j < b.size(); j++) {
      uint64_t mul = (uint64_t) a.data[i] * b.data[j] + res.data[i + j] + carry;
      res.data[i + j] = (uint32_t) (mul & UINT32_MAX);
      carry = (uint32_t) (mul >> 32);
    }
    res.data[i + b.size()] += carry;
  }
  res.negative = a.negative ^ b.negative;
  res.normalize();
  return res;
}

//region Division
#define uint128_t unsigned __int128

void difference(big_integer& a, big_integer const& b, size_t index) {
  size_t start = a.size() - index;
  bool borrow = false;
  for (size_t i = 0; i < index; ++i) {
    uint32_t x = a.data[start + i];
    uint32_t y = (i < b.size() ? b.data[i] : 0);
    int64_t c = (int64_t) x - y - borrow;

    borrow = c < 0;
    c &= UINT32_MAX;
    a.data[start + i] = (uint32_t) c;
  }
}

inline big_integer shortdiv(big_integer const& a, uint32_t b) {
  big_integer tmp;
  uint64_t rest = 0, x;
  for (size_t i = 0; i < a.size(); i++) {
    x = (rest << 32) | a.data[a.size() - 1 - i];
    tmp.data.push_back((uint32_t) (x / b));
    rest = x % b;
  }
  reverse(tmp.data.begin(), tmp.data.end());
  tmp.normalize();
  return tmp;
}

big_integer operator/(const big_integer& f, big_integer const& one) {
  big_integer a = f, b = one, tmp, dq;
  a.negative = b.negative = false;

  if (a < b) { return ZERO; }

  if (b.size() == 1) {
    tmp = shortdiv(a, b.data[0]);
    tmp.negative = f.negative ^ one.negative;
    return tmp;
  }

  a.data.push_back(0);

  size_t m = b.size() + 1, n = a.size();
  tmp.data.resize(n - m + 1);
  uint32_t qt;
  for (size_t i = m, j = tmp.data.size() - 1; i <= n; ++i, --j) {
    uint128_t x = (((uint128_t) a.data[a.size() - 1] << 64) |
                   ((uint128_t) a.data[a.size() - 2] << 32) |
                   ((uint128_t) a.data[a.size() - 3]));
    uint128_t y = (((uint128_t) b.data[b.size() - 1] << 32) |
                   (uint128_t) b.data[b.size() - 2]);

    qt = std::min((uint32_t) (x / y), UINT32_MAX);

    dq = b * qt;

    bool flag = true;
    for (size_t k = 1; k <= a.size(); k++) {
      if (a.data[a.size() - k] != (m - k < dq.size() ? dq.data[m - k] : 0)) {
        flag = a.data[a.size() - k] > (m - k < dq.size() ? dq.data[m - k] : 0);
        break;
      }
    }

    if (!flag) {
      qt--;
      dq -= b;
    }
    tmp.data[j] = qt;
    difference(a, dq, m);
    if (!a.data.back()) { a.data.pop_back(); }
  }

  tmp.normalize();
  tmp.negative = f.negative ^ one.negative;
  return tmp;
}

#undef uint128_t
//endregione

big_integer operator%(const big_integer& a, big_integer const& b) {
  return a - (a / b) * b;
}
// endregion

// region bitwise binary operators
big_integer operator&(big_integer a, big_integer const& b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a & b; });
}

big_integer operator|(big_integer a, big_integer const& b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a | b; });
}

big_integer operator^(big_integer a, big_integer const& b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a ^ b; });
}

big_integer operator<<(big_integer a, int b) {
  size_t block_shift = static_cast<size_t>(b) >> 5u,
    inner_shift = static_cast<size_t>(b) & 31u;
  uint32_t carry = 0, tmp;
  for (uint32_t& i : a.data) {
    tmp = (i >> (32 - inner_shift));
    i = ((i << inner_shift) | carry);
    carry = tmp;
  }
  if (carry > 0) { a.data.push_back(carry); }
  a.data.resize(a.data.size() + block_shift);
  for (size_t i = a.data.size(); i > block_shift; i--) {
    a.data[i - 1] = a.data[i - block_shift - 1];
  }
  std::fill(a.data.begin(), a.data.begin() + block_shift, 0);
  return a;
}

big_integer operator>>(big_integer a, int b) {
  size_t block_shift = static_cast<size_t> (b) >> 5u,
    inner_shift = static_cast<size_t> (b) & 31u;
  uint32_t carry = 0, tmp, offset = (1u << inner_shift) - 1;
  for (size_t i = block_shift; i < a.data.size(); i++) { a.data[i - block_shift] = a.data[i]; }
  a.data.resize(a.data.size() - block_shift);
  for (auto i = a.data.rbegin(); i != a.data.rend(); i++) {
    tmp = (*i & offset) << (32 - inner_shift);
    *i = ((*i >> inner_shift) | carry);
    carry = tmp;
  }
  a.normalize();
  if (a.negative) { a--; }
  return a;
}
// endregion

// region io operators
std::ostream& operator<<(std::ostream& s, big_integer const& a) {
  return s << to_string(a);
}

std::istream& operator>>(std::istream& in, big_integer& a) {
  std::string s;
  in >> s;
  a = big_integer(s);
  return in;
}
// endregion