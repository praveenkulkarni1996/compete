#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

int main() {
  map<int, int> best;
  for (int four = 0; four <= 8; four++) {
    for (int nine = 0; nine <= 48; nine++) {
      const int sum = four * 4 + nine * 9;
      if (best.contains(sum)) {
        best[sum] = min(best[sum], four + nine);
      } else {
        best[sum] = four + nine;
      }
    }
  }
  for (int fortynine = 1; fortynine <= 9; fortynine++) {
    const int subtract = 49 * fortynine;
    erase_if(best, [&](auto item) {
      const auto [key, value] = item;
      return best.contains(key - subtract);
    });
  }
  int n;
  cin >> n;
  int64 ans = 0;
  for (auto [k, v] : best) {
    ans += max(n - v + 1, 0);
  }
  cout << ans << endl;
}
