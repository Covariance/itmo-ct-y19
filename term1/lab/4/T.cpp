#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = true;

typedef long long ll;

int n;
vector<vector<pair<int, int>>> g;
vector<long long> subtreeSize, len, ans;

void dfs2(int v, int parent, long long pathLen, long long pathSize, int edge) {
    pathLen += pathSize;
    for (int i = 0; i < (int) g[v].size(); i++) {
        if (g[v][i].fs != parent) {
            dfs2(
                g[v][i].fs,
                v,
                pathLen + len[v] - len[g[v][i].fs] - subtreeSize[g[v][i].fs],
                pathSize + subtreeSize[v] - subtreeSize[g[v][i].fs],
                g[v][i].sc);
        }
    }
    if (edge != -1) {
        ans[edge] = len[v] * pathSize + pathLen * subtreeSize[v];
    }
}

void dfs(int v, int parent) {
    subtreeSize[v] = 1;
    len[v] = 0;
    for (int i = 0; i < (int) g[v].size(); i++) {
        if (g[v][i].fs != parent) {
            dfs(g[v][i].fs, v);
            subtreeSize[v] += subtreeSize[g[v][i].fs];
            len[v] += len[g[v][i].fs] + subtreeSize[g[v][i].fs];
        }
    }
    if (parent == -1) {
        dfs2(0, -1, 0, 0, -1);
    }
}

int main() {
    if (!debug) {
        freopen("treedp.in", "r", stdin);
        freopen("treedp.out", "w", stdout);
    }
    int n;
    cin >> n;
    g.resize(n);
    ans.resize(n - 1);
    subtreeSize.resize(n);
    len.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(make_pair(b, i));
        g[b].push_back(make_pair(a, i));
    }
    dfs(0, -1);
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
