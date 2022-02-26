#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = false;

int n;
vector<vector<pair<int, int>>> g;
vector<long long> childrenSum;
vector<long long> d;

void dfs(int v = 0, int parent = -1) {
    for (size_t i = 0; i < g[v].size(); i++) {
        if (g[v][i].fs != parent) {
            dfs(g[v][i].fs, v);
            childrenSum[v] += max(d[g[v][i].fs], childrenSum[g[v][i].fs]);
        }
    }
    for (size_t i = 0; i < g[v].size(); i++) {
        if (g[v][i].fs != parent) {
            d[v] = max(d[v], childrenSum[v]
                                - max(childrenSum[g[v][i].fs], d[g[v][i].fs])
                                    + g[v][i].sc
                                        + childrenSum[g[v][i].fs]);
        }
    }
}

int main() {
    if (!debug) {
        freopen("matching.in", "r", stdin);
        freopen("matching.out", "w", stdout);
    }
    cin >> n;
    g.resize(n);
    for (int i = 0; i <  n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));
    }
    childrenSum.resize(n, 0);
    d.resize(n, 0);
    dfs();
    cout << max(d[0], childrenSum[0]);
    return 0;
}
