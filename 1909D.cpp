#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

using int64 = int64_t;

int64 recdown(int64 a, int64 b, int64 k, int64 &counter) {
  assert(a > k);
  assert(b > k);
  if (a < b) {
    return recdown(b, a, k, counter);
  }
  if (a == b) {
    return b;
  }
  int64 steps = (a - b + (b - k - 1)) / (b - k);
  counter += steps;
  return recdown(b, a - (steps * (b - k)), k, counter);
}

int64 recup(int64 a, int64 b, int64 k, int64 &counter) {
  assert(a < k);
  assert(b < k);
  if (a > b) {
    return recup(b, a, k, counter);
  }
  if (a == b) {
    return b;
  }
  int64 steps = (b - a + (k - b - 1)) / (k - b);
  counter += steps;
  return recup(b, a + steps * (k - b), k, counter);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    int64 k;
    cin >> n >> k;
    vector<int64> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    sort(a.begin(), a.end());
    int64 large = *a.rbegin();
    int64 small = *a.begin();
    if (small == large) {
      cout << 0 << "\n";
      continue;
    } else if (large < k) {
      int64 common = a[0];
      int64 counter = 0;
      for (int64 x : a) common = recup(common, x, k, counter);
      counter = 0;
      for (int64 x : a) common = recup(common, x, k, counter);
      cout << counter << "\n";
    } else if (k < small) {
      int64 common = a[0];
      int64 counter = 0;
      for (int64 x : a) common = recdown(common, x, k, counter);
      counter = 0;
      for (int64 x : a) common = recdown(common, x, k, counter);
      cout << counter << "\n";
    } else {
      cout << -1 << "\n";
    }
  }
}