class dsu {
  int n;
  vector<int> e;

  int pfind(const int x) { return (e[x] < 0 ? x : e[x] = pfind(e[x])); }

 public:
  dsu() : n(0), comp(0) {}
  explicit dsu(const int n) : n(n), comp(n), e(n, -1) {}

  int comp;

  int find(const int x) {
    assert(0 <= x and x < n);
    return pfind(x);
  }

  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y];
    e[y] = x;
    comp--;
    return true;
  }

  bool same(const int x, const int y) { return (find(x) == find(y)); }

  int size(const int x) { return -e[find(x)]; }

  vector<vector<int>> components() {
    vector<vector<int>> res(n);
    for (int x = 0; x < n; x++) {
      res[pfind(x)].push_back(x);
    }
    res.erase(remove_if(res.begin(), res.end(),
                        [&](const vector<int> &v) { return v.empty(); }),
              res.end());
    return res;
  }
};
