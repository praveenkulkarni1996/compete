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

int readInt() {
  int x;
  cin >> x;
  return x;
}

string readString() {
  string s;
  cin >> s;
  return s;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t = readInt();
  const int kLimit = (100 * 26) + 1;
  vector<mint> fact(kLimit);
  fact[0] = 1;
  for (int i = 1; i < kLimit; i++) {
    fact[i] = mint(i) * fact[i - 1];
  }

  auto nCr = [&](const int64 n, const int64 r) -> mint {
    assert(0 <= r);
    assert(r <= n);
    assert(n < kLimit);
    return fact[n] / (fact[r] * fact[n - r]);
  };

  while (t--) {
    const string s = readString();
    const int64 n = s.size();
    int64 L = 0;
    for (char ch : s) {
      L += (ch - 'a' + 1);
    }
    mint ans = mint(0);
    mint sign = mint(1);
    for (int r = 0; r <= (L - n) / 26; r++) {
      ans += sign * nCr(n, r) * nCr(L - 1 - 26 * r, n - 1);
      sign *= mint(-1);
    }
    cout << (ans - mint(1)) << endl;
  }
}