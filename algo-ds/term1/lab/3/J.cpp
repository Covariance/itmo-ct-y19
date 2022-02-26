#include <bits/stdc++.h>

using namespace std;

bool debug = false;

const long long p = 1000003;

struct node {
    int messages;
    int sum;
    int parent;
    int rank;
};

vector<node> g;
int n = 0;
long long zerg = 0;

int findParent(int v) {
    if (g[v].parent == v) {
        return v;
    }
    int ancestor = findParent(g[v].parent);
    if (ancestor != g[v].parent) {
        g[v].sum += g[g[v].parent].sum;
    }
    g[v].parent = ancestor;
    return ancestor;
}

void unite(int a, int b) {
    if ((a = findParent(a)) != (b = findParent(b))) {
        zerg = (13ll * zerg + 11ll) % p;
        if (g[a].rank < g[b].rank) {
            swap(a, b);
        }
        g[a].rank += (g[a].rank == g[b].rank) ? 1 : 0;
        g[b].sum -= g[a].sum;
        g[b].parent = a;
    }
}

int getUnread(int v) {
    int u = findParent(v);
    int ret = g[v].sum - g[v].messages;
    if (v != u) {
        ret += g[u].sum;
    }
    g[v].messages += ret;
    return ret;
}

int main() {
    int m, t, a, b, ans;
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n; i++) {
        g[i].messages = 0;
        g[i].parent = i;
        g[i].rank = 0;
        g[i].sum = 0;
    }
    for (int i = 0; i < m; i++) {
        cin >> t;
        if (t == 1) {
            cin >> a;
            g[findParent((a + (int)zerg) % n)].sum++;
            zerg = (30ll * zerg + 239ll) % p;       /// ненавижу эти числа кстати
        }
        if (t == 2) {
            cin >> a >> b;
            unite((a + (int)zerg) % n, (b + (int)zerg) % n);
        }
        if (t == 3) {
            cin >> a;
            ans = getUnread((a + (int)zerg) % n);
            cout << ans << "\n";
            zerg = (100500ll * zerg + (long)ans) % p;       /// это число кстати тоже не очень люблю
        }
    }
    return 0;
}
