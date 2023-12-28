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

template <unsigned int N>
string to_string(modint<N> num) {
  return to_string(num.x);
}

const int kLimit = 1e5;

int readInt() {
  int x;
  cin >> x;
  return x;
}

using mint = modint<kMod>;

int main() {
  const int n = readInt();
  vector<int> a(n);
  for (int &x : a) {
    x = readInt();
  }
  sort(a.begin(), a.end());
  const int kLimit = a[n - 1];
  vector<vector<int>> factors(kLimit + 1);
  for (int f = 1; f <= kLimit; f++) {
    for (int mult = f; mult <= kLimit; mult += f) {
      factors[mult].push_back(f);
    }
  }
  vector<int> counts(kLimit + 1);
  for (int f = 1; f <= kLimit; f++) {
    counts[f] = distance(lower_bound(a.begin(), a.end(), f), a.end());
  }
  mint total = mint(0);
  for (int lcm = 1; lcm <= a[n - 1]; lcm++) {
    mint local = mint(1);
    const int nfactors = factors[lcm].size();
    for (int id = 0; id < nfactors - 1; id++) {
      const int factor = factors[lcm][id];
      const int nextfactor = factors[lcm][id + 1];
      const int options = counts[factor] - counts[nextfactor];
      local *= mint(id + 1).power(options);
    }
    local *= mint(nfactors).power(counts[lcm]) -
             mint(nfactors - 1).power(counts[lcm]);
    total += local;
  }
  cout << total << endl;
  return 0;
}
