#include "bits/stdc++.h"
using namespace std;

using int64 = long long;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  const int kInf = 1e6 + 1;
  multiset<pair<int, bool>> opts;
  opts.insert({kInf, false});

  const int n = readInt();
  int64 profit = 0;
  for (int i = 0; i < n; i++) {
    const int x = readInt();
    const auto [small, to_replace] = *opts.begin();
    if (x <= small) {
      opts.insert({x, false});
    } else {
      profit += x - small;
      opts.erase(opts.begin());
      opts.insert({x, true});
      if (to_replace) {
        opts.insert({small, false});
      }
    }
  }
  cout << profit << endl;
}
