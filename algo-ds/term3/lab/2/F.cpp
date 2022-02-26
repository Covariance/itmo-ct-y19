//
// Created by covariance on 21.10.2020.
//
#include <bits/stdc++.h>

#define INF 1000000000000000007L
#define fs first
#define sc second

using namespace std;

typedef struct edge {
  int from;
  int to;
  int w;

  edge(int from, int to, int w)
    : from(from)
    , to(to)
    , w(w) {}
} edge;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<edge> edges;
  vector<long long> d;
  vector<int> last_changed;

  int n;
  cin >> n;
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      int w;
      cin >> w;
      if (w != 1e9) {
        edges.emplace_back(i, j, w);
      }
    }
  }

  last_changed.assign(n, -1);

  d.assign(n, INF);
  d[0] = 0;

  int change = -1;
  for (int i = 0; i != n; ++i) {
    change = -1;
    for (edge edge : edges) {
      if (d[edge.to] > d[edge.from] + edge.w) {
        d[edge.to] = d[edge.from] + edge.w;
        change = last_changed[edge.to] = edge.from;
      }
    }
  }

  if (change == -1) {
    cout << "NO\n";
    return 0;
  }

  for (int i = 0; i != n; ++i) {
    change = last_changed[change];
  }

  int current = change;
  vector<int> answer(1, current);

  do {
    current = last_changed[current];
    answer.push_back(current);
  } while (current != change);

  reverse(answer.begin(), answer.end());
  cout << "YES\n" << answer.size() << "\n";
  for (int cyc : answer) {
    cout << cyc + 1 << ' ';
  }

  return 0;
}
