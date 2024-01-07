#include "bits/stdc++.h"
using namespace std;
using int64 = long long;

template <class node, class F = std::function<node(const node &, const node &)>>
class SegTree {
  int n = 0;
  std::vector<node> t;
  F unite;

  void build(const int x, const int l, const int r,
             const std::vector<node> &a) {
    if (l == r) {
      t[x] = a[l];
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    build(x + 1, l, mid, a);
    build(y, mid + 1, r, a);
    t[x] = unite(t[x + 1], t[y]);
  }

  void update(const int x, const int l, const int r, const int p,
              const node &v) {
    if (l == p and p == r) {
      t[x] = v;
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (p <= mid) {
      update(x + 1, l, mid, p, v);
    } else {
      update(y, mid + 1, r, p, v);
    }
    t[x] = unite(t[x + 1], t[y]);
  }

  node query(const int x, const int l, const int r, const int ql,
             const int qr) const {
    if (ql <= l and r <= qr) {
      return t[x];
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    if (qr <= mid) {
      return query(x + 1, l, mid, ql, qr);
    } else if (mid < ql) {
      return query(y, mid + 1, r, ql, qr);
    } else {
      return unite(query(x + 1, l, mid, ql, qr), query(y, mid + 1, r, ql, qr));
    }
  }

  void debug_node(const int x, const vector<int> &path) const {
    for (int i = 0; i < path.size(); i++) {
      cerr << path[i] << (i == path.size() - 1 ? ": " : " -> ");
    }
    cerr << t[x] << '\n';
  }

  void print_tree(const int x, const int l, const int r,
                  vector<int> path) const {
    path.push_back(x);
    if (l == r) {
      debug_node(x, path);
      return;
    }
    const int mid = (l + r) / 2;
    const int y = 2 * (mid - l + 1) + x;
    print_tree(x + 1, l, mid, path);
    print_tree(y, mid + 1, r, path);
    debug_node(x, path);
  }

 public:
  SegTree() = default;
  explicit SegTree(const int n, const node e, F f)
      : n(n), t(2 * n - 1, e), unite(std::move(f)) {}
  explicit SegTree(const std::vector<node> &a, F f)
      : n(a.size()), t(2 * (a.size()) - 1), unite(std::move(f)) {
    build(0, 0, n - 1, a);
  }

  void update(const int p, const node &v) {
    assert(0 <= p and p < n);
    update(0, 0, n - 1, p, v);
  }

  [[nodiscard]] node query(const int l, const int r) const {
    assert(0 <= l and l <= r and r < n);
    return query(0, 0, n - 1, l, r);
  }

  void print_tree() const {
    print_tree(0, 0, n - 1, {});
    cerr << "----------\n\n";
  }
};

struct node {
  int64 wine = 0;
  int64 minus = 0;
  int64 plus = 0;
  int64 spare = 0;
};

inline auto unite = [](const node &a, const node &b) {
  node c;
  const int64 brew = min(a.plus, b.minus);
  c.wine = a.wine + b.wine + brew;
  c.plus = min(a.plus - brew, b.spare) + b.plus;
  c.minus = a.minus + min(a.spare, b.minus - brew);
  c.spare = min(a.spare - min(b.minus - brew, a.spare),
                b.spare - min(a.plus - brew, b.spare));
  return c;
};

inline auto to_node(int64 a, int64 b, int64 c) {
  node x;
  x.wine = min(a, b);
  x.plus = min(a - x.wine, c);
  x.minus = b - x.wine;
  x.spare = c - x.plus;
  return x;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int64> a(n), b(n), c(n);
  c[n - 1] = 1e18;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  for (int i = 0; i < n - 1; i++) {
    cin >> c[i];
  }
  SegTree<node> tree(n, node(), unite);

  for (int i = 0; i < n; i++) {
    tree.update(i, to_node(a[i], b[i], c[i]));
  }
  for (int i = 0; i < q; i++) {
    int64 pi, ai, bi, ci;
    cin >> pi >> ai >> bi >> ci;
    tree.update(pi - 1, to_node(ai, bi, ci));
    cout << tree.query(0, n - 1).wine << "\n";
  }
}