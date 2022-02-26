//
// Created by covariance on 26.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> match;
vector<bool> used;

bool kun(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int son : g[v]) {
        if (match[son] == -1 || kun(match[son])) {
            match[son] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    g.assign(n, vector<int>());
    match.assign(n, -1);

    for (int i = 0; i != m; ++i) {
        int left, right;
        cin >> left >> right;
        g[left - 1].push_back(right - 1);
    }

    for (int i = 0; i != n; ++i) {
        used.assign(n, false);
        kun(i);
    }

    int ans = n;
    for (int par : match) {
        if (par != -1) {
            --ans;
        }
    }
    cout << ans << endl;
    return 0;
}
