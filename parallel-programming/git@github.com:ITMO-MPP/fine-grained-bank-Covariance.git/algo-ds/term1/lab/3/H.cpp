#include <bits/stdc++.h>

using namespace std;

bool debug = false;

struct node {
    int color;
    int parent;
    int rank;
};

vector<node> g;
int shift, n = 0;

int findParent(int v) {
    if (g[v].parent == v) {
        return v;
    }
    return findParent(g[v].parent);
}

int shifted(int a) {
	int ans = (a + shift) % n;
	if (ans == 0) ans = n;
	return ans - 1;
}

int findColor(int v) {
    if (g[v].parent == v) {
        return g[v].color;
    }
    return (g[v].color ^ findColor(g[v].parent));
}

void unite(int a, int b) {
    bool changeColor = findColor(a) == findColor(b);
    if ((a = findParent(a)) != (b = findParent(b))) {
        if (g[a].rank < g[b].rank) {
            swap(a, b);
        }
        g[b].color ^= (changeColor) ? 1 : 0;
        g[b].parent = a;
        g[a].rank += (g[a].rank == g[b].rank) ? 1 : 0;
    }
}

int main() {
    int m, t, a, b;
    cin >> n >> m;
    g.resize(n);

    for (int i = 0; i < n; i++) {
        g[i].color = 0;
        g[i].parent = i;
        g[i].rank = 0;
    }
    for (int i = 0; i < m; i++) {
        cin >> t >> a >> b;
        if (!debug) {
            a = shifted(a);
            b = shifted(b);
        }
        if (t == 0) {
            unite(a, b);
        } else {
            if (debug) {
                cout <<findColor(a) <<' ' <<findColor(b) <<endl;
            } else {
                if (findColor(a) == findColor(b)) {
                    cout << "YES\n";
                    shift = (shift + 1) % n;
                } else {
                    cout << "NO\n";
                }
            }
        }
        if (debug) {
            cout <<endl <<"graph:\n";
            for (int j = 0; j < n; j++) {
                cout << j << ' ' << g[j].parent << ' ' << g[j].color << ' ' << findColor(j) << endl;
            }
            cout << endl;
        }
    }
    return 0;
}
