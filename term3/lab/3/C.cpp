//
// Created by covariance on 12.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int m, n;
vector<vector<int>> g;
vector<bool> used;
vector<int> Lminus, L, R;

void dfs(int v) {
    used[v] = true;
    if (v < m) {
        L[v] = -1;
    } else {
        R.push_back(v);
    }
    for (int son : g[v]) {
        if (!used[son]) {
            dfs(son);
        }
    }
}

int main() {
    cin >> m >> n;

    g.resize(m + n);

    for (int i = 0; i != m; ++i) {
        int cnt;
        cin >> cnt;
        while (cnt--) {
            int to;
            cin >> to;
            g[i].emplace_back(m + to - 1);
        }
    }

    L.resize(m);
    for (int i = 0; i != m; ++i) {
        int to;
        cin >> to;
        L[i] = i;
        if (to > 0) {
            g[m + to - 1].emplace_back(i);
        } else {
            Lminus.emplace_back(i);
        }
    }

    used.resize(m + n, false);
    for (int lminus : Lminus) {
        if (!used[lminus]) {
            dfs(lminus);
        }
    }

    vector<int> Lnew;
    for (int l : L) {
        if (l != -1) {
            Lnew.emplace_back(l);
        }
    }
    sort(Lnew.begin(), Lnew.end());
    sort(R.begin(), R.end());

    cout << Lnew.size() + R.size() << endl;
    cout << Lnew.size() << ' ';
    for (int l : Lnew) {
        cout << l + 1 << ' ';
    }

    cout << endl << R.size() << ' ';
    for (int r : R) {
        cout << r - m + 1 << ' ';
    }

    return 0;
}
