//
// Created by covariance on 07.05.2020.
//

#include "big_integer.h"

big_integer::big_integer() : value(1), sign(false) {}

big_integer::big_integer(int x) : value(1, (uint32_t) std::abs((int64_t) x)), sign(x < 0) {}

big_integer::big_integer(uint32_t x) : value(1, x), sign(false) {}

big_integer::big_integer(uint64_t x) : value(0), sign(false) {
  value.push_back((uint32_t) (x & (UINT32_MAX)));
  value.push_back((uint32_t) (x >> 32));
}


static const big_integer ZERO(0);
static const big_integer ONE(1);
static const big_integer TWO(2);
static const big_integer TEN(10);

big_integer::big_integer(std::string const &s) : value(1, 0), sign(false) {
  size_t i = (s.length() > 0 && (s[0] == '-' || s[0] == '+')) ? 0 : -1;
  while (++i < s.length()) *this = (*this * TEN) + (s[i] - '0');
  sign = (s[0] == '-');
  normalize();
}

std::string to_string(big_integer const &a) {
  if (a == big_integer()) return "0";

  std::string ans;
  big_integer tmp(a);

  while (tmp != ZERO) {
    ans += char('0' + (tmp % TEN).value[0]);
    tmp /= TEN;
  }
  if (a.sign) ans += '-';
  reverse(ans.begin(), ans.end());
  return ans;
}

void big_integer::swap(big_integer &one) {
  std::swap(value, one.value);
  std::swap(sign, one.sign);
}

big_integer &big_integer::operator=(big_integer const &one) {
  big_integer tmp(one);
  swap(tmp);
  return *this;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
  return *this = *this + rhs;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
  return *this = *this - rhs;
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
  return *this = *this * rhs;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
  return *this = *this / rhs;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
  return *this = *this % rhs;
}

big_integer &big_integer::operator&=(big_integer const &rhs) {
  return *this = *this & rhs;
}

big_integer &big_integer::operator|=(big_integer const &rhs) {
  return *this = *this | rhs;
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
  return *this = *this ^ rhs;
}

big_integer &big_integer::operator<<=(int rhs) {
  return *this = *this << rhs;
}

big_integer &big_integer::operator>>=(int rhs) {
  return *this = *this >> rhs;
}

big_integer big_integer::operator+() const {
  return big_integer(*this);
}

big_integer big_integer::operator-() const {
  big_integer tmp(*this);
  tmp.sign = !tmp.sign;
  tmp.normalize();
  return tmp;
}

big_integer big_integer::operator~() const {
  return -(*this) - ONE;
}

big_integer &big_integer::operator++() {
  return (*this += ONE);
}

const big_integer big_integer::operator++(int) {
  const big_integer ret = *this;
  *this += 1;
  return ret;
}

big_integer &big_integer::operator--() {
  return (*this -= ONE);
}

const big_integer big_integer::operator--(int) {
  const big_integer ret = *this;
  *this -= 1;
  return ret;
}

bool operator==(big_integer const &a, big_integer const &b) {
  return (a.sign == b.sign && a.value == b.value);
}

bool operator!=(big_integer const &a, big_integer const &b) {
  return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
  if (a.sign != b.sign) return a.sign;

  if (a.sign) {
    if (a.size() != b.size()) {
      return a.size() > b.size();
    }
    size_t i = a.size();
    while (i--) {
      if (a.value[i] != b.value[i]) {
        return a.value[i] > b.value[i];
      }
    }
    return false;
  } else {
    if (a.size() != b.size()) {
      return a.size() < b.size();
    }
    size_t i = a.size();
    while (i--) {
      if (a.value[i] != b.value[i]) {
        return a.value[i] < b.value[i];
      }
    }
    return false;
  }
}

bool operator>(big_integer const &a, big_integer const &b) {
  return (b < a);
}

bool operator<=(big_integer const &a, big_integer const &b) {
  return !(a > b);
}

bool operator>=(big_integer const &a, big_integer const &b) {
  return !(a < b);
}

big_integer operator+(big_integer a, big_integer const &b) {
  if (a.sign != b.sign) {
    return (a.sign ? b - (-a) : a - (-b));
  }

  size_t size = std::max(a.size(), b.size());
  uint64_t sum = 0, carry = 0;
  big_integer res;
  res.value.resize(size + 1, 0);
  for (size_t i = 0; i < size; i++) {
    sum = carry;
    if (i < a.size()) sum += a.value[i];
    if (i < b.size()) sum += b.value[i];

    carry = (sum > UINT32_MAX ? 1 : 0);

    res.value[i] = (uint32_t) (sum & UINT32_MAX);
  }
  res.value[size] = (uint32_t) carry;
  res.sign = a.sign;
  res.normalize();
  return res;
}

big_integer operator-(big_integer a, big_integer const &b) {
  if (a.sign != b.sign) {
    return (a.sign ? -((-a) + b) : a + (-b));
  }
  if (a.sign) return (-b) - (-a);
  if (a < b) return -(b - a);
  uint32_t sub = 0, carry = 0;
  big_integer res;
  res.value.resize(a.size());

  for (size_t i = 0; i < a.size(); i++) {
    if (i >= b.size()) {
      if (a.value[i] >= carry) {
        res.value[i] = a.value[i] - carry;
        carry = 0;
      } else {
        res.value[i] = UINT32_MAX;
        carry = 1;
      }
      continue;
    }

    if (a.value[i] >= b.value[i]) {
      sub = a.value[i] - b.value[i];
      if (sub >= carry) {
        sub -= carry;
        carry = 0;
      } else {
        sub = UINT32_MAX;
        carry = 1;
      }
    } else {
      sub = UINT32_MAX - (b.value[i] - a.value[i]) + 1 - carry;
      carry = 1;
    }

    res.value[i] = sub;
  }
  res.normalize();
  return res;
}

big_integer operator*(big_integer a, big_integer const &b) {
  if (a == ZERO || b == ZERO) return big_integer();

  big_integer res;
  res.value.resize(a.size() + b.size(), 0);

  for (size_t i = 0; i < a.size(); i++) {
    uint32_t carry = 0;
    for (size_t j = 0; j < b.size(); j++) {
      uint64_t mul = (uint64_t) a.value[i] * b.value[j] + res.value[i + j] + carry;
      res.value[i + j] = (uint32_t) (mul & UINT32_MAX);
      carry = (uint32_t) (mul >> 32);
    }
    res.value[i + b.size()] += carry;
  }
  res.sign = a.sign ^ b.sign;
  res.normalize();
  return res;
}

//region Division
#define uint128_t unsigned __int128
void difference(big_integer &a, big_integer const &b, size_t index) {
  size_t start = a.size() - index;
  bool borrow = false;
  for (size_t i = 0; i < index; ++i) {
    uint32_t x = a.value[start + i];
    uint32_t y = (i < b.size() ? b.value[i] : 0);
    int64_t c = (int64_t) x - y - borrow;

    borrow = c < 0;
    c &= UINT32_MAX;
    a.value[start + i] = (uint32_t) c;
  }
}

inline big_integer shortdiv(big_integer const &a, uint32_t b) {
  big_integer tmp;
  uint64_t rest = 0, x;
  for (size_t i = 0; i < a.size(); i++) {
    x = (rest << 32) | a.value[a.size() - 1 - i];
    tmp.value.push_back((uint32_t) (x / b));
    rest = x % b;
  }
  reverse(tmp.value.begin(), tmp.value.end());
  tmp.normalize();
  return tmp;
}

big_integer operator/(const big_integer& f, big_integer const &one) {
  big_integer a = f, b = one, tmp, dq;
  a.sign = b.sign = false;

  if (a < b) return ZERO;

  if (b.size() == 1) {
    tmp = shortdiv(a, b.value[0]);
    tmp.sign = f.sign ^ one.sign;
    return tmp;
  }

  a.value.push_back(0);

  size_t m = b.size() + 1, n = a.size();
  tmp.value.resize(n - m + 1);
  uint32_t qt;
  for (size_t i = m, j = tmp.value.size() - 1; i <= n; ++i, --j) {
    uint128_t x = (((uint128_t) a.value[a.size() - 1] << 64) |
                   ((uint128_t) a.value[a.size() - 2] << 32) |
                   ((uint128_t) a.value[a.size() - 3]));
    uint128_t y = (((uint128_t) b.value[b.size() - 1] << 32) |
                   (uint128_t) b.value[b.size() - 2]);

    qt = std::min((uint32_t) (x / y), UINT32_MAX);

    dq = b * qt;

    bool flag = true;
    for (size_t k = 1; k <= a.size(); k++) {
      if (a.value[a.size() - k] != (m - k < dq.size() ? dq.value[m - k] : 0)) {
        flag = a.value[a.size() - k] > (m - k < dq.size() ? dq.value[m - k] : 0);
        break;
      }
    }

    if (!flag) {
      qt--;
      dq -= b;
    }
    tmp.value[j] = qt;
    difference(a, dq, m);
    if (!a.value.back()) a.value.pop_back();
  }

  tmp.normalize();
  tmp.sign = f.sign ^ one.sign;
  return tmp;
}
#undef uint128_t
//endregione

big_integer operator<<(big_integer a, int b) {
  a *= big_integer((uint64_t(1) << b % 32));
  for (int i = 0; i < b / 32; i++) a.value.push_back(0);
  return a;
}

big_integer operator>>(big_integer a, int b) {
  for (int i = 0; i < b / 32 && a.size(); i++) a.value.pop_back();
  if (a < ZERO) a -= big_integer((uint64_t(1) << b % 32) - 1);
  if (b % 32 == 31) a /= TWO;
  a /= big_integer((uint32_t(1) << std::min(30, b % 32)));
  return a;
}

big_integer operator%(const big_integer& a, big_integer const &b) {
  return a - (a / b) * b;
}

big_integer bitwise(big_integer &a, big_integer const &b, const std::function<uint32_t(uint32_t, uint32_t)> &op) {
  size_t max_size = std::max(a.size(), b.size());
  big_integer tmp1 = a.convert(max_size), tmp2 = b.convert(max_size), res = res.convert(max_size);

  for (size_t i = 0; i < max_size; i++) res.value[i] = op(tmp1.value[i], tmp2.value[i]);

  if (op((uint32_t) a.sign, (uint32_t) b.sign)) return -((-res).convert(max_size));
  else return res;
}

big_integer operator&(big_integer a, big_integer const &b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a & b; });
}

big_integer operator|(big_integer a, big_integer const &b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a | b; });
}

big_integer operator^(big_integer a, big_integer const &b) {
  return bitwise(a, b, [](uint32_t a, uint32_t b) { return a ^ b; });
}

size_t big_integer::size() const {
  return value.size();
}

big_integer big_integer::convert(size_t n) const {
  big_integer res(*this);

  res.value.resize(n);

  if (sign) {
    res.sign = false;
    std::for_each(res.value.begin(), res.value.end(), [](uint32_t &a) { a = ~a; });
    res += ONE;
  }

  return res;
}

void big_integer::normalize() {
  while (size() > 1 && value.back() == 0) value.pop_back();
  if (zero()) {
    sign = false;
  }
}

bool big_integer::zero() const {
  return (value.size() == 1 && value[0] == 0);
}

std::ostream &operator<<(std::ostream &s, big_integer const &a) {
  return s << to_string(a);
}

std::istream &operator>>(std::istream &in, big_integer &a) {
  std::string s;
  in >> s;
  a = big_integer(s);
  return in;
}