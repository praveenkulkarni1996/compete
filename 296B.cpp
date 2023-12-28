#include "bits/stdc++.h"
using namespace std;
using int64 = long long int;

const int kMod = 1e9 + 7;

template <unsigned int M>
struct modint {
  int64 x;

  modint(const modint<M> &m) : x(m.x) {}
  explicit modint(const int64 _x) : x((_x >= 0 ? _x % M : M + (_x % (int)M))) {}
  explicit modint(const int _x) : x((_x >= 0 ? _x % M : M + (_x % (int)M))) {}
  explicit modint() : x(0) {}

  [[nodiscard]] modint<M> inv() const { return power(M - 2); }

  [[nodiscard]] modint<M> power(int64 exp) const {
    modint<M> res(1), base(x);
    while (exp) {
      if (exp & 1) res *= base;
      base *= base;
      exp >>= 1;
    }
    return res;
  }

  [[nodiscard]] modint<M> power(modint<M> &exp) const { return power(exp.x); }

  modint<M> &operator=(const int _x) {
    x = (_x >= 0 ? _x % M : M + (_x % M));
    return *this;
  }

  modint<M> &operator=(const int64 _x) {
    x = (_x >= 0 ? _x % M : M + (_x % M));
    return *this;
  }

  modint<M> &operator=(const modint<M> &other) {
    x = other.x;
    return *this;
  }

  modint<M> &operator+=(const modint<M> &other) {
    x += other.x;
    x -= (x >= M ? M : 0);
    return *this;
  }

  modint<M> &operator-=(const modint<M> &other) {
    x += M - other.x;
    x -= (x >= M ? M : 0);
    return *this;
  }

  modint<M> &operator*=(const modint<M> &other) {
    x *= other.x;
    x %= M;
    return *this;
  }

  modint<M> &operator/=(const modint<M> &other) {
    x = (*this * other.inv()).x;
    return *this;
  }

  friend modint<M> operator+(const modint<M> &lhs, const modint<M> &rhs) {
    return (modint(lhs) += rhs);
  }

  friend modint<M> operator-(const modint<M> &lhs, const modint<M> &rhs) {
    return (modint(lhs) -= rhs);
  }

  friend modint<M> operator*(const modint<M> &lhs, const modint<M> &rhs) {
    return (modint(lhs) *= rhs);
  }

  friend modint<M> operator/(const modint<M> &lhs, const modint<M> &rhs) {
    return (modint(lhs) /= modint(rhs));
  }

  friend bool operator==(const modint<M> &lhs, const modint<M> &rhs) {
    return (lhs.x == rhs.x);
  }

  friend bool operator!=(const modint<M> &lhs, const modint<M> &rhs) {
    return (lhs.x != rhs.x);
  }

  friend std::ostream &operator<<(std::ostream &os, const modint<M> &m) {
    return (os << m.x);
  }

  friend std::istream &operator>>(std::istream &in, modint<M> &m) {
    return (in >> m.x);
  }

  modint<M> &operator++() {
    x++;
    x = (x == M ? 0 : x);
    return *this;
  }

  modint<M> &operator--() {
    x = (x == 0 ? M : x);
    x--;
    return *this;
  }

  modint<M> operator++(int) {
    modint result = *this;
    ++*this;
    return result;
  }

  modint<M> operator--(int) {
    modint result = *this;
    --*this;
    return result;
  }
};

using mint = modint<kMod>;

template <typename T>
T read() {
  T x;
  cin >> x;
  return x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  const int n = read<int>();
  const string s = read<string>();
  const string t = read<string>();
  mint total = mint(1);
  mint sless = mint(1);
  mint tless = mint(1);
  mint equal = mint(1);
  for (int i = 0; i < n; i++) {
    if (s[i] == '?' and t[i] == '?') {
      total *= mint(100);
      equal *= mint(10);
      sless *= mint(55);
      tless *= mint(55);
    } else if (s[i] == '?') {
      int x = t[i] - '0';
      total *= mint(10);
      equal *= mint(1);
      sless *= mint(x + 1);
      tless *= mint(10 - x);
    } else if (t[i] == '?') {
      int x = s[i] - '0';
      total *= mint(10);
      equal *= mint(1);
      sless *= mint(10 - x);
      tless *= mint(x + 1);
    } else {
      int svalue = s[i] - '0';
      int tvalue = t[i] - '0';
      total *= mint(1);
      equal *= mint(svalue == tvalue);
      sless *= mint(svalue <= tvalue);
      tless *= mint(tvalue <= svalue);
    }
  }
  cout << (total - sless - tless + equal) << endl;
}