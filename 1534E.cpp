#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int readInt() {
  int x;
  cin >> x;
  return x;
}

int main() {
  const int n = readInt();
  const int k = readInt();
  vector<vector<int>> g(n + 1);

  for (int on = 0; on <= n; on++) {
    for (int both = max(0, on + k - n); both <= min(k, on); both++) {
      const int next = (k - both) + (on - both);
      g[on].push_back(next);
    }
  }

  const int kUnreachable = 1e8;

  auto bfs = [&](const int start) -> pair<vector<int>, vector<int>> {
    vector<int> dist(n + 1, kUnreachable);
    vector<int> pi(n + 1, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (not q.empty()) {
      int cur = q.front();
      q.pop();
      for (int nbr : g[cur]) {
        if (dist[nbr] > dist[cur] + 1) {
          dist[nbr] = dist[cur] + 1;
          pi[nbr] = cur;
          q.push(nbr);
        }
      }
    }
    return {dist, pi};
  };

  auto calcpath = [k](const int end, const vector<int> &pi) {
    vector<pair<int, int>> path;
    for (int cur = end; pi[cur] != -1; cur = pi[cur]) {
      int both = (pi[cur] - cur + k) / 2;
      path.push_back({pi[cur], both});
    }
    reverse(path.begin(), path.end());
    return path;
  };

  auto [dist, pi] = bfs(0);
  if (dist[n] == kUnreachable) {
    cout << -1 << endl;
    return 0;
  }
  auto path = calcpath(n, pi);

  vector<bool> on(n, false);

  auto ask = [&](int both, const int k) {
    int activate = k - both;
    assert(0 <= both);
    assert(0 <= activate);
    cout << "? ";
    for (int i = 0; i < n; i++) {
      if (on[i] and both > 0) {
        on[i] = false;
        both--;
        cout << i + 1 << " ";
      } else if (not on[i] and activate > 0) {
        on[i] = true;
        activate--;
        cout << i + 1 << " ";
      }
    }
    cout << endl;
    return readInt();
  };

  int answer = 0;
  for (auto [node, both] : path) {
    answer ^= ask(both, k);
  }
  cout << "! " << answer << endl;
}