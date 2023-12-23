#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int ask(const string &s) {
  cout << s << endl;
  int editdist = readInt();
  if (editdist == 0) {
    exit(0);
  }
  return editdist;
}

int main() {
  const int acount = 300 - ask(string(300, 'a'));
  const int bcount = 300 - ask(string(300, 'b'));
  if (acount == 0) {
    ask(string(bcount, 'b'));
    return 0;
  }
  if (bcount == 0) {
    ask(string(acount, 'a'));
    return 0;
  }
  const int n = acount + bcount;
  string guess = string(n, 'a');
  int baseline = bcount;
  for (int i = 0; i < guess.length(); i++) {
    guess[i] = 'b';
    if (ask(guess) < baseline) {
      baseline--;
    } else {
      guess[i] = 'a';
    }
  }
}