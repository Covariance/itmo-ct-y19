#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = false;
const int INF = 2e9;

int main() {
    size_t n, m;
    if (!debug) {
        freopen("salesman.in", "r", stdin);
        freopen("salesman.out", "w", stdout);
    }
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());
    for (size_t i = 0; i < m; i++) {
        size_t a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back(make_pair(b, c));
        g[b].push_back(make_pair(a, c));
    }
    vector<vector<int>> d;
    vector<size_t> pw(n, 1);
    for (size_t i = 1; i < n; i++) {
        pw[i] = 2 * pw[i - 1];
    }
    size_t maxpw = 2 * pw[n - 1];
    d.resize(maxpw, vector<int>(n, INF));
    for (size_t i = 0; i < n; i++) {
        d[pw[i]][i] = 0;
    }
    for (size_t i = 1; i < maxpw; i++) {
        for (size_t j = 0; j < n; j++) {
            if (d[i][j] != INF) {
                for (size_t v = 0; v < g[j].size(); v++) {
                    int to = g[j][v].fs, cost = g[j][v].sc;
                    if ((pw[to] & i) == 0) {
                        d[pw[to] + i][to] = min(d[pw[to] + i][to], d[i][j] + cost);
                    }
                }
            }
        }
    }
    int ans = INF;
    for (size_t i = 0; i < n; i++) {
        ans = min(ans, d[maxpw - 1][i]);
    }
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans;
    }
    return 0;
}
