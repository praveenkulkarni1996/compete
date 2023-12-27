#include <algorithm>
#include <bit>
#include <iostream>
#include <vector>
using namespace std;

using int64 = int64_t;

const int64 kImpossible = -1e15;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int64> a(n);
  vector<vector<int64>> dp(1 << n, vector<int64>(n, kImpossible));
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    dp[1 << i][i] = a[i];
  }
  vector<vector<int64>> c(n, vector<int64>(n));
  for (int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;
    cin >> c[x - 1][y - 1];
  }
  int64 answer = kImpossible;
  for (int mask = 1; mask < (1 << n); mask++) {
    for (int i = 0, ibit = 1; i < n; i++, ibit <<= 1) {
      if ((ibit & mask) == 0) {
        continue;
      }
      for (int j = 0, jbit = 1; j < n; j++, jbit <<= 1) {
        if ((jbit & mask) != 0) {
          continue;
        }
        dp[mask | jbit][j] =
            max(dp[mask | jbit][j], dp[mask][i] + a[j] + c[i][j]);
      }
      if (popcount(static_cast<uint64_t>(mask)) == m) {
        answer = max(answer, dp[mask][i]);
      }
    }
  }
  cout << answer << endl;
}
