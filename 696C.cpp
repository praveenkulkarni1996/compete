#include "bits/stdc++.h"
using namespace std;
using int64 = long long;
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
using matrix = array<array<mint, 2>, 2>;

template <unsigned int N>
string to_string(modint<N> num) {
  return to_string(num.x);
}

matrix operator*(const matrix &a, const matrix &b) {
  matrix c;
  for (int row : {0, 1}) {
    for (int col : {0, 1}) {
      c[row][col] = a[row][0] * b[0][col] + a[row][1] * b[1][col];
    }
  }
  return c;
}

matrix operator+(const matrix &a, const matrix &b) {
  matrix c;
  for (int row : {0, 1}) {
    for (int col : {0, 1}) {
      c[row][col] = a[row][col] + b[row][col];
    }
  }
  return c;
}

matrix power(matrix a, int64 n) {
  matrix x = {array<mint, 2>({mint(1), mint(0)}),
              array<mint, 2>({mint(0), mint(1)})};
  while (n > 0) {
    if (n & 1) {
      x = (x * a);
    }
    a = a * a;
    n >>= 1;
  }
  return x;
}

int64 readInt64() {
  int64 x;
  cin >> x;
  return x;
}

int main() {
  const int64 k = readInt64();
  matrix N = {array<mint, 2>({mint(1), mint(2)}),
              array<mint, 2>({mint(1), mint(0)})};
  mint d(2);
  for (int i = 0; i < k; i++) {
    const int64 a = readInt64();
    N = power(N, a);
    d = d.power(a);
  }
  const mint n = N[1][1] / mint(2);
  cout << n << "/" << (d / mint(2)) << "\n";
}