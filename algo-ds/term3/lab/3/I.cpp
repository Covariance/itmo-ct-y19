//
// Created by covariance on 13.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<size_t> first_exist;
vector<int> result;

void dfs(int cur = 0) {
    while (first_exist[cur] != g[cur].size()) {
        dfs(g[cur][first_exist[cur]++]);
    }
    result.push_back(cur);
}

int main() {
    int d, k;
    cin >> d >> k;

    if (k == 1) {
        for (int i = 0; i != d; ++i) {
            cout << i;
        }
        return 0;
    }

    if (d == 1) {
        for (int i = 0; i != k; ++i) {
            cout << 0;
        }
        return 0;
    }

    int n = static_cast<int>(
            pow(static_cast<long double>(d),
                static_cast<long double>(k - 1)));

    g.assign(n, vector<int>(d));
    first_exist.assign(n, 0);

    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != d; ++j) {
            g[i][j] = (i % (n / d)) * d + j;
        }
    }

    dfs();

    for (size_t i = 1; i != result.size(); ++i) {
        cout << result[i - 1] % d;
    }


    for (int i = 0; i != k - 1; ++i) {
        cout << '0';
    }

    return 0;
}
