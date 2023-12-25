#include <cassert>
#include <iostream>
using namespace std;

#define int64 int64_t

int readInt() {
  int x;
  cin >> x;
  return x;
}

int64 readInt64() {
  int64 x;
  cin >> x;
  return x;
}

struct State {
  int pos = -1;

  bool ask(int64 guess) {
    pos = guess;
    cout << "? " << guess << endl;
    return (readInt() == 1);
  }
};

void say(int64 answer) {
  cout << "= " << answer << endl;
  exit(0);
}

void alternate(State &state, int64 n) {
  state.ask(n);
  int front = 0, back = n;
  while (front + 1 < back) {
    bool resp;
    if (state.pos != front) {
      front++;
      resp = state.ask(front);
    } else {
      back--;
      resp = state.ask(back);
    }
    if (not resp) {
      say(back - front + 1);
    }
  }
  say(back - front);
}

int main() {
  const int64 n = readInt64();
  State state;
  alternate(state, n);
}
