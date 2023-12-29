#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

int main() {
  int n, k;
  cin >> n >> k;
  vector<int64> blue(n), red(n);
  for (int i = 0; i < n; i++) {
    cin >> blue[i] >> red[i];
  }
  const int64 bluesum = accumulate(blue.begin(), blue.end(), 0LL);
  const int64 redsum = accumulate(red.begin(), red.end(), 0LL);
  if ((bluesum % k) + (redsum % k) < k) {
    cout << (bluesum / k) + (redsum / k) << endl;
    return 0;
  }
  vector<bool> prv(k);
  vector<bool> nxt(k);
  prv[0] = true;
  for (int shrub = 0; shrub < n; shrub++) {
    nxt = prv;
    for (int b = 1; b <= min(k - 1LL, blue[shrub]); b++) {
      const int r = k - b;
      if (r > red[shrub]) continue;
      for (int prvb = 0; prvb < k; prvb++) {
        if (not prv[prvb]) continue;
        nxt[(b + prvb) % k] = true;
      }
    }
    swap(prv, nxt);
  }
  for (int b = 0; b <= bluesum % k; b++) {
    const int r = k - b;
    if (prv[b] and r <= (redsum % k)) {
      cout << 1 + (bluesum / k) + (redsum / k) << endl;
      return 0;
    }
  }
  cout << (bluesum / k) + (redsum / k) << endl;
}