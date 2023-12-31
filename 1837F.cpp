#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

template <typename T>
using max_heap = priority_queue<T, vector<T>, less<T>>;

bool check(const vector<int> &a, const int64 minutes, const int k) {
  assert(minutes >= 0);
  const int n = a.size();
  vector<int> prefix(n);
  vector<int> suffix(n);
  {
    max_heap<int> take;
    int64 used = 0;
    for (int i = 0; i < n; i++) {
      take.push(a[i]);
      used += a[i];
      while (used > minutes) {
        used -= take.top();
        take.pop();
      }
      prefix[i] = take.size();
    }
  }
  {
    max_heap<int> take;
    int64 used = 0;
    for (int i = n - 1; i >= 0; i--) {
      take.push(a[i]);
      used += a[i];
      while (used > minutes) {
        used -= take.top();
        take.pop();
      }
      suffix[i] = take.size();
    }
  }
  if (prefix[n - 1] >= k) return true;
  if (suffix[0] >= k) return true;
  for (int i = 0; i < n - 1; i++) {
    if (prefix[i] + suffix[i + 1] >= k) {
      return true;
    }
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int64 hi = accumulate(a.begin(), a.end(), 0LL);
    int64 lo = 0;
    while (lo < hi) {
      int64 mid = (lo + hi) / 2;
      if (check(a, mid, k)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    assert(lo == hi);
    cout << lo << endl;
  }
}