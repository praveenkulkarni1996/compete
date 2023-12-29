#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

const int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  int t = readInt();
  while (t--) {
    const int n = readInt();
    vector<vector<int>> ppl(n);
    for (int i = 0; i < n; i++) {
      int get = readInt();
      int pay = readInt();
      ppl[get].push_back(pay);
    }
    vector<int> need(n);
    int cnt = ppl[0].size();
    for (int i = 1; i < n; i++) {
      need[i] = max(0, i - cnt);
      cnt += ppl[i].size();
    }
    min_heap<int> h;
    vector<int64> paid;
    for (int i = n - 1; i >= 0; i--) {
      for (int p : ppl[i]) {
        h.push(p);
      }
      while (paid.size() < need[i]) {
        paid.push_back(h.top());
        h.pop();
      }
    }
    cout << accumulate(paid.begin(), paid.end(), 0LL) << endl;
  }
}
