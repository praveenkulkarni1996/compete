#include "bits/stdc++.h"
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

const int kMod = 1e9 + 7;
const int kMax = 70;

const vector<int> primes = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                            31, 37, 41, 43, 47, 53, 59, 61, 67};

int main() {
  const int n = readInt();
  vector<int> freq(kMax + 1);
  for (int i = 0; i < n; i++) {
    freq[readInt()]++;
  }

  auto primemask = [&](int x) -> int {
    int ans = 0;
    for (int i = 0; i < primes.size(); i++) {
      while ((x % primes[i]) == 0) {
        ans ^= (1 << i);
        x /= primes[i];
      }
    }
    return ans;
  };

  vector<int> pow2(n + 1);
  pow2[0] = 1;
  for (int i = 1; i <= n; i++) {
    pow2[i] = (pow2[i - 1] << 1) % kMod;
  }

  map<int, int> prv;
  map<int, int> cur;
  prv[0] = 1;
  for (int i = 1; i <= kMax; i++) {
    if (freq[i] == 0) continue;
    const int ways = pow2[freq[i] - 1];
    for (const auto [key, value] : prv) {
      for (const int nxt : {key, key ^ primemask(i)}) {
        cur[nxt] = (cur[nxt] + ((value * 1LL * ways) % kMod)) % kMod;
      }
    }
    swap(cur, prv);
    cur.clear();
  }
  cout << (prv[0] + kMod - 1) % kMod << endl;
}