#include <bits/stdc++.h>
#pragma GCC optimize("-Ofast")

using namespace std;

bool debug = false;

struct node {
	int parent;
	int segmentParent;
	int rang;
};

vector<node> g;

inline int findSegmentParent(int v) {
    return (g[v].segmentParent == v) ?
    v : (g[v].segmentParent = findSegmentParent(g[v].segmentParent));
}

inline int findParent(int v) {
	return (g[v].parent == v) ? v : (g[v].parent = findParent(g[v].parent));
}

inline void unite(int a, int b) {
	if ((a = findParent(a)) != (b = findParent(b))) {
		if (g[a].rang < g[b].rang) {
			swap(a, b);
		}
		g[b].parent = a;
		if (g[a].rang == g[b].rang) {
            g[a].rang++;
		}
	}
}

inline void segmentUnite(int a, int b) {
    if ((a = findSegmentParent(a)) == (b = findSegmentParent(b))) {
        return;
    }
    g[a].segmentParent = b;
}

inline void multiUnite(int a, int b) {
    for (int i = (a = findSegmentParent(a)) + 1; i <= b; i++) {
        int j = i - 1;
        i = findSegmentParent(i);
        unite(a, i);
        segmentUnite(j, i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
	int n, a, b, t, q;
	scanf("%d %d\n", &n, &q);
	g.resize(n);

	for (int i = 0; i < n; i++) {
		g[i].parent = i;
		g[i].segmentParent = i;
		g[i].rang = 0;
	}
	for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &t, &a, &b);
        if (t == 1) {
            unite(a - 1, b - 1);
        }
        if (t == 2) {
            multiUnite(a - 1, b - 1);
        }
        if (t == 3) {
            (findParent(g[a - 1].segmentParent) == findParent(g[b - 1].segmentParent)) ?
                printf("YES\n") : printf("NO\n");
        }
	}
	return 0;
}
