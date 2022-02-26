#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = false;
const int MIN_INT = -2147483648;

int main() {
    if (!debug) {
        freopen("levenshtein.in", "r", stdin);
        freopen("levenshtein.out", "w", stdout);
    }
    string a, b;
    cin >> a >> b;
    int n = a.length() + 1, m = b.length() + 1;
    vector<vector<int>> d(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        d[i][0] = i;
    }
    for (int i = 0; i < m; i++) {
        d[0][i] = i;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i - 1] != b[j - 1]) {
                d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + 1);
            } else {
                d[i][j] = d[i - 1][j - 1];
            }
        }
    }
    cout << d[n - 1][m - 1];
    return 0;
}
