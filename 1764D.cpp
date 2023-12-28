#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

int power(int64 base, int exp, const int mod) {
  int64 res = 1;
  while (exp) {
    if (exp & 1) {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  const int n = readInt();
  const int p = readInt();
  vector<int64> fact(n + 1);
  vector<int64> invfact(n + 1);
  fact[0] = invfact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = (i * fact[i - 1]) % p;
    invfact[i] = power(fact[i], p - 2, p);
    assert((fact[i] * invfact[i]) % p == 1);
  }

  auto nCr = [&](const int n, const int r) -> int64 {
    return (((fact[n] * invfact[r]) % p) * invfact[n - r]) % p;
  };

  const int t = n / 2;

  int64 ans = (n % 2 == 0) ? fact[n - 2] : 0;
  for (int i = t; i <= n - 2; i++) {
    for (int j = 0; j <= n - i - 2; j++) {
      const int64 last = 2 * t - i;
      const int64 select = nCr(n - i - 2, j);
      const int64 permute = fact[i + j - 1];
      const int64 res = (((last * select) % p) * permute) % p;
      ans = (ans + res) % p;
    }
  }
  ans = (ans * n) % p;
  cout << ans << endl;
}