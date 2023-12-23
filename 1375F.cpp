#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

#define int int64_t

int readInt() {
  int x;
  cin >> x;
  return x;
}

int ask(int y) {
  cout << y << endl;
  int code = readInt();
  if (code == 0) {
    exit(0);
  }
  return code;
}

int maxcode(int a, int b, int c) {
  int mx = max({a, b, c});
  if (mx == a) {
    return 1;
  } else if (mx == b) {
    return 2;
  } else {
    return 3;
  }
}

void game(int a, int b, int c) {
  const int guess = (3 * max({a, b, c})) - a - b - c;
  const int code = ask(guess);
  const bool do_retry = (code == maxcode(a, b, c));
  if (code == 1) {
    a += guess;
  } else if (code == 2) {
    b += guess;
  } else {
    c += guess;
  }
  if (do_retry) {
    game(a, b, c);
  }
  ask((max({a, b, c}) - min({a, b, c})) / 2);
  assert(false);
}

int32_t main() {
  cout << "First" << endl;
  int a = readInt();
  int b = readInt();
  int c = readInt();
  game(a, b, c);
}