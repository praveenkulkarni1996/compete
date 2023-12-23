#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  int n = readInt();

  auto askXor = [&n](const int i, const int j) {
    assert(0 <= i and i < n);
    assert(0 <= j and j < n);
    assert(i != j);
    cout << "XOR " << i + 1 << " " << j + 1 << endl;
    return readInt();
  };

  auto askAnd = [&n](const int i, const int j) {
    assert(0 <= i and i < n);
    assert(0 <= j and j < n);
    assert(i != j);
    cout << "AND " << i + 1 << " " << j + 1 << endl;
    return readInt();
  };

  vector<vector<int>> freq(n);
  int duplicate = -1;
  freq[0].push_back(0);
  for (int i = 1; i < n; i++) {
    const int xorv = askXor(0, i);
    freq[xorv].push_back(i);
    if (freq[xorv].size() > 1) {
      duplicate = xorv;
    }
  }

  vector<int> a(n);

  if (duplicate != -1) {
    int x = freq[duplicate][0];
    int y = freq[duplicate][1];
    a[0] = askAnd(x, y) ^ duplicate;
  } else {
    assert(freq[1].size() == 1);
    assert(freq[n - 2].size() == 1);
    a[0] = askAnd(0, freq[1][0]) | askAnd(0, freq[n - 2][0]);
  }

  for (int xorv = 0; xorv < n; xorv++) {
    for (int index : freq[xorv]) {
      a[index] = xorv ^ a[0];
    }
  }
  cout << "! ";
  for (int x : a) {
    cout << x << " ";
  }
  cout << endl;
}
