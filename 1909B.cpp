#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  int t = readInt();
  while (t--) {
    const int n = readInt();
    vector<long long> a(n);
    for (auto &x : a) {
      cin >> x;
    }
    sort(a.begin(), a.end());
    long long ans = a[1] - a[0];
    for (int i = 1; i < n; i++) {
      ans = gcd(ans, a[i] - a[0]);
    }
    cout << 2 * ans << "\n";
  }
}