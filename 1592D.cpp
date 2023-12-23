#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

const int readInt() {
  int x;
  cin >> x;
  return x;
}

int ask(const vector<int> &nodes, const int limit) {
  assert(1 <= limit and limit < nodes.size());
  cout << "? " << limit + 1;
  for (int i = 0; i <= limit; i++) {
    cout << " " << nodes[i] + 1;
  }
  cout << endl;
  return readInt();
}

void say(const int a, const int b) {
  assert(a >= 0);
  assert(b >= 0);
  assert(a != b);
  cout << "! " << a + 1 << " " << b + 1 << endl;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  const int n = readInt();
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u = readInt() - 1;
    int v = readInt() - 1;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<int> preorder;
  vector<int> parent(n, -1);
  preorder.reserve(n);
  function<void(int, int)> dfs = [&](int x, int p = -1) {
    preorder.push_back(x);
    parent[x] = p;
    for (int nbr : g[x]) {
      if (nbr == p) continue;
      dfs(nbr, x);
    }
  };
  dfs(0, -1);

  assert(preorder.size() == n);

  const int maxgcd = ask(preorder, n - 1);
  int lo = 1;
  int hi = n - 1;

  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (ask(preorder, mid) == maxgcd) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  assert(lo == hi);
  say(preorder[lo], parent[preorder[lo]]);
}