#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> fr;
vector< vector<int> > g;
int n, i;
bool debug = false;

ll dfs(int v, int depth) {
    ll retv = 0;
    if (debug) {
        for (int j = 0; j < depth; j++) cout <<'\t';
        cout << "vertix v = " << v << endl;
    }
    for (int newv: g[v]) {
        retv += dfs(newv, depth + 1);
    }
    if (v < n) {
        retv += fr[v] * depth;
    }
    return retv;
}

int main() {
    if (!debug) {
        freopen("huffman.in", "r", stdin);
        freopen("huffman.out", "w", stdout);
    }
    set< pair<ll, int> > que;
    cin >> n;
    g.resize(n);
    fr.resize(n);
    for (i = 0; i < n; i++) {
        cin >> fr[i];
        que.insert(make_pair(fr[i], i));
        g[i].resize(0);
    }
    while (que.size() > 1) {
        pair<ll, int> mn1 = *(que.begin());
        que.erase(que.begin());
        pair<ll, int> mn2 = *(que.begin());
        que.erase(que.begin());
        g.resize(i + 1);
        g[i].resize(0);
        g[i].push_back(mn1.second);
        g[i].push_back(mn2.second);
        que.insert(make_pair(mn1.first + mn2.first, i++));
    }
    cout << dfs(g.size() - 1, 0);
    return 0;
}
