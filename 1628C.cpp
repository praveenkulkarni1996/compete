#include <iostream>
#include <vector>
using namespace std;

inline int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  int kTests = readInt();
  for (int testcase = 0; testcase < kTests; testcase++) {
    const int n = readInt();
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        a[i][j] = readInt();
      }
    }
    int answer = 0;
    for (int diag = 0; diag < 2 * n - 1; diag += 4) {
      int r = (diag < n) ? diag : n - 1;
      int c = (diag < n) ? 0 : diag - n + 1;
      while (0 <= r and c < n) {
        answer ^= a[r][c];
        answer ^= a[r][n - 1 - c];
        r -= 2;
        c += 2;
      }
    }
    cout << answer << "\n";
  }
  return 0;
}