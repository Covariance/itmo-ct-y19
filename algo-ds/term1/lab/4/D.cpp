#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = false;
const int MIN_INT = -2147483648;

int main() {
    if (!debug) {
        freopen("knapsack.in", "r", stdin);
        freopen("knapsack.out", "w", stdout);
    }
    int n, m;
    cin >> n >> m;
    vector<int> w;
    w.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    vector<int> c;
    c.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));
    vector<vector<bool>> take(m + 1, vector<bool>(n + 1, false));
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (w[j - 1] <= i && d[i - w[j - 1]][j - 1] + c[j - 1] >= d[i][j - 1]) {
                d[i][j] = d[i - w[j - 1]][j - 1] + c[j - 1];
                take[i][j] = true;
            } else {
                d[i][j] = d[i][j - 1];
            }
            d[i][j] = max(d[i][j - 1],
                    (w[j - 1] <= i) ? (d[i - w[j - 1]][j - 1] + c[j - 1]) : MIN_INT);
        }
    }
    int mx = MIN_INT;
    int mx_ind = 0;
    vector<int> ans;
    for (int i = 0; i < m + 1; i++) {
        if (mx <= d[i][n]) {
            mx = d[i][n];
            mx_ind = i;
        }
    }

    while (mx_ind > 0 && n > 0) {
        if (take[mx_ind][n]) {
            ans.push_back(n);
            mx_ind -= w[n - 1];
        }
        n--;
    }
    cout << ans.size() << endl;
    for (int ind : ans) {
        cout << ind <<' ';
    }
    return 0;
}
