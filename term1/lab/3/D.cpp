#include <bits/stdc++.h>

using namespace std;

bool debug = true;

vector<int> g;

int findParent(int v) {
	if (g[v] == v) return v;
	return (g[v] = findParent(g[v]));
}

void unite(int a, int b) {
	g[a] = findParent(g[b]);
}

int main() {
	int n, a;
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n; i++) {
		g[i] = i;
	}
	for (int i = 0; i < n; i++) {
        cin >> a;
        a--;
        int empty = findParent(a);
        cout << empty + 1 << ' ';
        unite(empty, (empty + 1) % n);
	}
	return 0;
}
