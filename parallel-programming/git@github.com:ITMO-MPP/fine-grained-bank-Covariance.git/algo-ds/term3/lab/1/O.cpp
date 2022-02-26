//
// Created by covariance on 01.10.2020.
//
#include <bits/stdc++.h>

#define fs first
#define sc second

using namespace std;

vector<vector<int>> g, gr;
vector<bool> used, res;
vector<int> sorted, comp;

size_t no(size_t i) {
  return i ^ 1u;
}

void dfs1(int v) {
  used[v] = true;
  for (int son : g[v]) {
    if (!used[son]) {
      dfs1(son);
    }
  }
  sorted.push_back(v);
}

void dfs2(int v, int comp_cnt) {
  comp[v] = comp_cnt;
  for (int son : gr[v]) {
    if (comp[son] == -1) {
      dfs2(son, comp_cnt);
    }
  }
}

bool two_sat() {
  size_t n = g.size();
  used.assign(n, false);
  comp.assign(n, -1);
  sorted.clear();
  for (size_t i = 0; i != n; ++i) {
    if (!used[i]) {
      dfs1(i);
    }
  }

  int comp_cnt = 0;
  for (size_t i = 0; i != n; ++i) {
    if (comp[sorted[n - i - 1]] == -1) {
      dfs2(sorted[n - i - 1], comp_cnt++);
    }
  }

  for (size_t i = 0; i != n; ++i) {
    if (comp[i] == comp[no(i)]) {
      return false;
    }
  }

  res.clear();
  res.resize(n);

  for (size_t i = 0; i != n; ++i) {
    res[i] = comp[i] > comp[no(i)];
  }

  return true;
}

void add_edge(int from, int to) {
  g[from].push_back(to);
  gr[to].push_back(from);
}

int main() {
  int n;
  cin >> n;

  vector<int> color(n);
  for (int i = 0; i != n; ++i) {
    cin >> color[i];
    --color[i];
  }

  vector<int> ring(2 * n);
  for (int i = 0; i != 2 * n; ++i) {
    cin >> ring[i];
    --ring[i];
  }

  g.assign(2 * n, vector<int>());
  gr.assign(2 * n, vector<int>());

  unordered_map<int, pair<int, int>> places;

  for (int i = 0; i != 2 * n; ++i) {
    if (places.find(ring[i]) == places.end()) {
      places[ring[i]] = {i, 0};
    } else {
      places[ring[i]].sc = i;
    }
  }

  for (int i = 0; i != 2 * n; ++i) {
    int j = (i + 1) % (2 * n);
    if (color[ring[i]] == color[ring[j]] && ring[i] != ring[j]) {
      if (i == places[ring[i]].fs && j == places[ring[j]].fs) {
        add_edge(2 * ring[i], 2 * ring[j] + 1);
        add_edge(2 * ring[j], 2 * ring[i] + 1);
      }
      if (i == places[ring[i]].fs && j == places[ring[j]].sc) {
        add_edge(2 * ring[i], 2 * ring[j]);
        add_edge(2 * ring[j] + 1, 2 * ring[i] + 1);
      }
      if (i == places[ring[i]].sc && j == places[ring[j]].fs) {
        add_edge(2 * ring[i] + 1, 2 * ring[j] + 1);
        add_edge(2 * ring[j], 2 * ring[i]);
      }
      if (i == places[ring[i]].sc && j == places[ring[j]].sc) {
        add_edge(2 * ring[i] + 1, 2 * ring[j]);
        add_edge(2 * ring[j] + 1, 2 * ring[i]);
      }
    }
  }

  if (!two_sat()) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    for (int i = 0; i != n; ++i) {
      cout <<(res[2 * i] ? places[i].fs : places[i].sc) + 1 << ' ';
    }
  }

  return 0;
}
