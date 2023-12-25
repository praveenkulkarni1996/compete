#include <algorithm>
#include <iostream>
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  int t = readInt();
  while (t--) {
    const int n = readInt();
    int notright = 0;
    int notleft = 0;
    int notup = 0;
    int notdown = 0;
    for (int i = 0; i < n; i++) {
      const int x = readInt();
      const int y = readInt();
      if (x <= 0) {
        notright++;
      }
      if (x >= 0) {
        notleft++;
      }
      if (y >= 0) {
        notdown++;
      }
      if (y <= 0) {
        notup++;
      }
    }
    if (max({notup, notdown, notleft, notright}) == n) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}