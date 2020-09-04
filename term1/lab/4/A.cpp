#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = true;

int main() {
    if (!debug) {
        freopen("matrix.in", "r", stdin);
        freopen("matrix.out", "w", stdout);
    }
    int n;
    cin >> n;
    vector<pair<int, int>> sz;
    vector<vector<long long>> d(n, vector<long long>(n, 0));
    vector<vector<string>> str(n, vector<string>(n));
    d.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> sz[i].fs >> sz[i].sc;
        d[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
        str[i][i] = "A";
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n - len; i++) {
            d[i][i + len] = d[i + 1][i + len] + sz[i].fs * sz[i].sc * sz[i + len].sc;
            for (int j = 0; j < len; j++) {
                long long newValue = d[i][i + j]
                                    + d[i + j + 1][i + len]
                                    + sz[i].fs * sz[i + j].sc * sz[i + len].sc;
                if (d[i][i + len] >= newValue) {
                    d[i][i + len] = newValue;
                    str[i][i + len] = "(" + str[i][i + j] + str[i + j + 1][i + len] + ")";
                }
            }
        }
    }
    cout << str[0][n - 1];
    return 0;
}
