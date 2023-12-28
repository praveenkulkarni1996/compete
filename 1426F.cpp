#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using int64 = long long;

int kMod = 1e9 + 7;

int readInt() {
  int x;
  cin >> x;
  return x;
}

string readStr() {
  string s;
  cin >> s;
  return s;
}

int main() {
  const int n = readInt();
  const string s = readStr();
  assert(s.size() == n);

  vector<int> pow3(n + 1);
  pow3[0] = 1;
  for (int i = 1; i <= n; i++) {
    pow3[i] = (3LL * pow3[i - 1]) % kMod;
  }

  vector<int> qprefix(n);
  vector<int> aprefix(n);
  qprefix[0] = s[0] == '?';
  aprefix[0] = s[0] == 'a';
  for (int i = 1; i < n; i++) {
    qprefix[i] = qprefix[i - 1] + (s[i] == '?');
    aprefix[i] = aprefix[i - 1] + (s[i] == 'a');
  }

  vector<int> qsuffix(n);
  vector<int> csuffix(n);
  qsuffix[n - 1] = s[n - 1] == '?';
  csuffix[n - 1] = s[n - 1] == 'c';
  for (int i = n - 2; i >= 0; i--) {
    qsuffix[i] = qsuffix[i + 1] + (s[i] == '?');
    csuffix[i] = csuffix[i + 1] + (s[i] == 'c');
  }

  assert(qprefix[n - 1] == qsuffix[0]);
  const int Q = qprefix[n - 1];

  auto counter = [&](int fixed, int q) -> int {
    int term1 = (fixed * 1LL * pow3[q]) % kMod;
    int term2 = (q == 0) ? 0 : ((q * 1LL * pow3[q - 1]) % kMod);
    return (term1 + term2) % kMod;
  };

  int ans = 0;
  for (int i = 1; i < n - 1; i++) {
    if (s[i] == 'a' or s[i] == 'c') continue;
    const int lhs = counter(aprefix[i - 1], qprefix[i - 1]);
    const int rhs = counter(csuffix[i + 1], qsuffix[i + 1]);
    ans = (ans + (lhs * 1LL * rhs) % kMod) % kMod;
  }
  cout << ans << endl;
}
