#include <bits/stdc++.h>

using namespace std;

bool debug = false;

struct node {
    int mn;
    int mx;
    int parent;
    int count;
};

vector<node> g;

int findParent(int v) {
    if (g[v].parent == v) return v;
    return (g[v].parent = findParent(g[v].parent));
}

void unite(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a != b) {
        if (g[a].count < g[b].count) {
            int t = b;
            b = a;
            a = t;
        }
        g[b].parent = a;
        g[a].count += g[b].count;
        if (g[b].mn < g[a].mn) g[a].mn = g[b].mn;
        if (g[b].mx > g[a].mx) g[a].mx = g[b].mx;
    }
}

int main() {
    int n, a, b;
    cin >> n;
    g.resize(n);

    for (int i = 0; i < n; i++) {
        g[i].mx = i + 1;
        g[i].mn = i + 1;
        g[i].parent = i;
        g[i].count = 1;
    }
    string s;
    while (cin >> s) {
        if (s[0] == 'u') {
            cin >> a >> b;
            unite(a - 1, b - 1);
        } else {
            cin >> a;
            a = findParent(a - 1);
            cout << g[a].mn << " " << g[a].mx << " " << g[a].count << endl;
        }
    }
    return 0;
}
