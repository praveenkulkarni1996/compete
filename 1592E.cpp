#include "bits/stdc++.h"
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  const int kBits = 20;
  int ans = 0;
  for (int k = kBits, mask = 0; k >= 0; k--) {
    const int bit = (1 << k);
    mask |= bit;
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; i++) {
      pref[i] = (a[i] & mask) ^ pref[i - 1];
    }
    vector<vector<int>> even(1 << kBits);
    vector<vector<int>> odd(1 << kBits);
    for (int i = 0; i <= n; i++) {
      (i % 2 == 0 ? even : odd)[pref[i]].push_back(i);
    }
    for (int r = 0, streak = n + 1; r <= n; r++) {
      if ((a[r] & bit) == 0) {
        streak = n + 1;
        continue;
      }
      streak = min(streak, r);
      const auto &parity = ((r % 2 == 0) ? even : odd);
      const auto &index = parity[pref[r]];
      const int l = *lower_bound(index.begin(), index.end(), streak - 1) + 1;
      if (l <= r) {
        ans = max(ans, r - l + 1);
      }
    }
  }
  cout << ans << endl;
}