//
// Created by covariance on 17.11.2020.
//
#include <bits/stdc++.h>

#define cendl cout << endl;

using namespace std;

int n, m, a;

// region BUMP
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];

inline void *operator new(size_t size) {
    char *res = mem + mpos;
    mpos += size;
    return (void *) res;
}

inline void operator delete(void *) {}
void operator delete(void*, size_t) {}
// endregion


bool kuhn(int v, const vector<vector<int>> &g, vector<int> &par, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int j = 0; j != m; ++j) {
        if (!g[v][j]) {
            continue;
        }
        if (par[j] == -1 || kuhn(par[j], g, par, used)) {
            par[j] = v;
            return true;
        }
    }
    return false;
}

void outer_kuhn(const vector<vector<int>> &g, vector<int> &par) {
    for (int i = 0; i != n; ++i) {
        vector<bool> nused(n, false);
        kuhn(i, g, par, nused);
    }
}

void dfs(int v, vector<vector<int>> &g, vector<int> &L, set<int> &R, vector<bool> &used) {
    if (used[v]) {
        return;
    }
    used[v] = true;
    if (v < n) {
        L.push_back(v);
    } else {
        R.erase(v);
    }

    for (int son : g[v]) {
        dfs(son, g, L, R, used);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<vector<int>> g(n, vector<int>(m, 1));
        vector<int> par(m, -1);

        for (int i = 0; i != n; ++i) {
            while (cin >> a) {
                if (a == 0) {
                    break;
                }
                g[i][a - 1] = 0;
            }
        }

        outer_kuhn(g, par);

        set<int> R;
        for (int i = 0; i != m; ++i) {
            R.insert(i + n);
        }

        vector<vector<int>> g2(n + m);
        unordered_set<int> Lminus;
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != m; ++j) {
                if (g[i][j]) {
                    if (par[j] == i) {
                        g2[n + j].push_back(i);
                    } else {
                        g2[i].push_back(n + j);
                    }
                }
            }
            Lminus.insert(i);
        }

        for (int i : par) {
            if (i != -1) {
                Lminus.erase(i);
            }
        }

        vector<int> L;
        vector<bool> used(n + m, false);
        for (int v : Lminus) {
            dfs(v, g2, L, R, used);
        }
        cout << L.size() + R.size();
        cendl
        cout << L.size() << ' ' << R.size();
        cendl

        sort(L.begin(), L.end());
        for (int i : L) {
            cout << i + 1 << ' ';
        }
        cendl
        for (int i : R) {
            cout << i + 1 - n << ' ';
        }
        cendl
    }
    return 0;
}
