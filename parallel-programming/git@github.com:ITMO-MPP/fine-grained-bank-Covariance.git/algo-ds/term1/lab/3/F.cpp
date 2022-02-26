#include <bits/stdc++.h>

using namespace std;

bool debug = false;

struct query {
    bool isCut;
    int v1;
    int v2;
};

struct vrt {
    int parent;
    int count;
};

vector<vrt> g;

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
    }
}

int main() {
    int n, a, b, m, k;
    vector<query> thread;
    vector<bool> ans;
    cin >> n >> m >> k;
    g.resize(n);
    thread.resize(k);

    for (int i = 0; i < n; i++) {
        g[i].count = 1;
        g[i].parent = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
    }

    string type;
    for (int i = 0; i < k; i++) {
        cin >> type >> thread[i].v1 >> thread[i].v2;
        thread[i].isCut = (type[0] == 'c');
    }

    for (int i = 0; i < k; i++) {
        if (thread[k - i - 1].isCut) {
            unite(thread[k - i - 1].v1 - 1, thread[k - i - 1].v2 - 1);
        } else {
            ans.push_back(findParent(thread[k - i - 1].v1 - 1)
                           == findParent(thread[k - i - 1].v2 - 1));
        }
    }
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[ans.size() - i - 1]) {
            cout << "YES\n";
        } else {
            cout <<"NO\n";
        }
    }
    return 0;
}
