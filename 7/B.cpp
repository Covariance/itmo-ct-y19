//
// Created by covariance on 22.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

class dsu {
  vector<uint32_t> par, rng;

  uint32_t get_root(uint32_t a) {
    return (par[a] == a) ? a : par[a] = get_root(par[a]);
  }

 public:
  dsu(size_t n) : par(n), rng(n, 0) {
    while (n--) {
      par[n] = n;
    }
  }

  bool same(uint32_t a, uint32_t b) {
    return get_root(a) == get_root(b);
  }

  void unite(uint32_t a, uint32_t b) {
    if (same(a, b)) {
      return;
    }
    a = get_root(a), b = get_root(b);
    if (rng[a] > rng[b]) {
      par[b] = a;
    } else {
      par[a] = b;
    }

    if (rng[a] == rng[b]) {
      ++rng[b];
    }
  }
};

struct edge {
  uint32_t a, b, i;
  uint64_t cost;

  edge(uint32_t a, uint32_t b, uint64_t cost, uint32_t i) : a(a), b(b), cost(cost), i(i) {}
};

vector<uint32_t> kruskal(uint32_t n, vector<edge> edge_list) {
  sort(edge_list.begin(),
       edge_list.end(),
       [](const edge &lhs, const edge &rhs) -> bool { return lhs.cost > rhs.cost; });
  vector<uint32_t> res;
  res.reserve(n - 1);

  dsu forest(n);
  for (edge e : edge_list) {
    if (!forest.same(e.a, e.b)) {
      forest.unite(e.a, e.b);
      res.emplace_back(e.i);
    }
  }

  return res;
}

int main() {
#ifndef DEBUG
  freopen("destroy.in", "r", stdin);
  freopen("destroy.out", "w", stdout);
#endif
  uint32_t n, m, a, b;
  uint64_t cost, s;
  cin >> n >> m >> s;
  vector<edge> edge_list;
  edge_list.reserve(m);

  for (uint32_t i = 0; i != m; ++i) {
    cin >> a >> b >> cost;
    --a, --b;
    edge_list.emplace_back(a, b, cost, i);
  }

  vector<uint32_t> deleted = kruskal(n, edge_list);
  sort(deleted.begin(), deleted.end());

  vector<edge> new_edge_list;
  new_edge_list.reserve(m - n + 1);

  for (uint32_t pnt = 0; pnt != deleted.size(); ++pnt) {
    for (uint32_t i = new_edge_list.size() + pnt; i != deleted[pnt]; ++i) {
      new_edge_list.emplace_back(edge_list[i]);
    }
  }
  for (uint32_t i = new_edge_list.size() + deleted.size(); i != edge_list.size(); ++i) {
    new_edge_list.emplace_back(edge_list[i]);
  }

  sort(new_edge_list.begin(),
       new_edge_list.end(),
       [](const edge &lhs, const edge &rhs) -> bool { return lhs.cost < rhs.cost; });

  set<uint32_t> ans;
  for (auto edge : new_edge_list) {
    if (edge.cost > s) {
      break;
    }
    ans.insert(edge.i + 1);
    s -= edge.cost;
  }

  cout << ans.size() << endl;
  for (auto i : ans) {
    cout << i << ' ';
  }

  return 0;
}