#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

int readInt() {
  int x;
  cin >> x;
  return x;
}

template <typename T>
vector<T> readVec(const int n) {
  vector<T> v(n);
  for (auto &x : v) {
    cin >> x;
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n = readInt();
  const int m = (n + 1) / 2;
  const vector<int64> a = readVec<int64>(m);
  const int64 x = readInt();

  vector<int64> psum(n);
  psum[0] = a[0];
  for (int i = 1; i < n; i++) {
    psum[i] = psum[i - 1] + (i < m ? a[i] : x);
  }

  vector<int64> minimas(n);
  for (int k = n - 2; k >= (n / 2); k--) {
    const int64 res = (n - k - 1) * x - psum[n - k - 2];
    minimas[k] = min(minimas[k + 1], res);
  }

  for (int k = (n / 2); k < n; k++) {
    if (psum[k] + minimas[k] > 0LL) {
      cout << k + 1 << endl;
      return 0;
    }
  }
  cout << -1 << endl;
}