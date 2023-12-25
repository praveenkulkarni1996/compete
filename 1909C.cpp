#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<long long> left(n), right(n), c(n);
    for (auto &x : left) cin >> x;
    for (auto &x : right) cin >> x;
    for (auto &x : c) cin >> x;
    set<long long> leftset;
    for (int i = 0; i < n; i++) {
      leftset.insert(-left[i]);
    }
    vector<int> sizes(n);
    sort(right.begin(), right.end());
    for (int i = 0; i < n; i++) {
      int leftv = *leftset.lower_bound(-right[i]);
      leftset.erase(leftv);
      sizes[i] = right[i] + leftv;
    }
    sort(sizes.begin(), sizes.end());
    sort(c.rbegin(), c.rend());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      ans += sizes[i] * c[i];
    }
    cout << ans << "\n";
  }
}
