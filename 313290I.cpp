#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector<vector<int>> g;
  int n;

  graph(int _n) : n(_n) { g.resize(n); }

  virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class digraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  digraph(int _n) : graph<T>(_n) {}

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int)edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }

  digraph<T> reverse() const {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    return rev;
  }
};

template <typename T>
vector<int> find_topsort(const digraph<T> &g) {
  vector<int> deg(g.n, 0);
  for (int id = 0; id < (int)g.edges.size(); id++) {
    deg[g.edges[id].to]++;
  }
  vector<int> x;
  for (int i = 0; i < g.n; i++) {
    if (deg[i] == 0) {
      x.push_back(i);
    }
  }
  for (int ptr = 0; ptr < (int)x.size(); ptr++) {
    int i = x[ptr];
    for (int id : g.g[i]) {
      auto &e = g.edges[id];
      int to = e.to;
      if (--deg[to] == 0) {
        x.push_back(to);
      }
    }
  }
  if ((int)x.size() != g.n) {
    return vector<int>();
  }
  return x;
}

int readInt() {
  int x;
  cin >> x;
  return x;
}

const int kInfinity = 1e9 + 1;

int main() {
  const int n = readInt();
  const int m = readInt();
  const int T = readInt();

  digraph<int> g(n);
  for (int i = 0; i < m; i++) {
    const int x = readInt();
    const int y = readInt();
    const int t = readInt();
    g.add(x - 1, y - 1, t);
  }
  vector<int> topo = find_topsort(g);

  const int root = find(topo.begin(), topo.end(), 0) - topo.begin();

  vector<vector<int>> dp(n, vector<int>(n + 1, kInfinity));
  vector<vector<int>> pi(n, vector<int>(n + 1, -1));
  dp[0][1] = 0;
  for (int i = root; i < n; i++) {
    const int x = topo[i];
    for (int id : g.g[x]) {
      const int y = g.edges[id].to;
      const int cost = g.edges[id].cost;
      for (int cnt = 1; cnt <= n; cnt++) {
        const int newcost = dp[x][cnt] + cost;
        if (newcost <= T and newcost < dp[y][cnt + 1]) {
          dp[y][cnt + 1] = newcost;
          pi[y][cnt + 1] = x;
        }
      }
    }
  }
  int path = 0;
  int prev = -1;
  for (int cnt = 1; cnt <= n; cnt++) {
    if (dp[n - 1][cnt] <= T) {
      path = cnt;
      prev = pi[n - 1][cnt];
    }
  }

  vector<int> ans;
  for (int node = n - 1; node != -1;) {
    assert(0 <= node and node < n);
    ans.push_back(node);
    node = pi[node][path];
    path--;
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";

  for (int x : ans) {
    cout << x + 1 << " ";
  }
  cout << endl;
}