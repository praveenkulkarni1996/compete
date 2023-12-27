#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int kMod = 1e9 + 7;

inline int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  const int n = readInt();
  const int m = readInt();
  const int b = readInt();
  const int mod = readInt();
  vector<int> a(n);
  for (int &x : a) {
    x = readInt();
  }
  vector<vector<int>> prv(m + 1, vector<int>(b + 1));
  vector<vector<int>> nxt(m + 1, vector<int>(b + 1));
  prv[0][0] = 1;
  nxt[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int lines = 1; lines <= m; lines++) {
      for (int bug = 0; bug <= b; bug++) {
        if (bug >= a[i]) {
          nxt[lines][bug] = nxt[lines - 1][bug - a[i]] + prv[lines][bug];
          nxt[lines][bug] %= mod;
        } else {
          nxt[lines][bug] = prv[lines][bug];
        }
      }
    }
    swap(prv, nxt);
  }
  int ans = 0;
  for (int bug = 0; bug <= b; bug++) {
    ans = (ans + prv[m][bug]) % mod;
  }
  cout << ans << endl;
}