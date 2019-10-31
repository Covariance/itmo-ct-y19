#include <bits/stdc++.h>

using namespace std;

bool debug = false;

int main() {
    if (!debug) {
        freopen("bwt.in", "r", stdin);
        freopen("bwt.out", "w", stdout);
    }
    string s; cin >> s;
    vector<string> rez;
    int n = s.length();
    rez.resize(n);
    for (int i = 0; i < n; i++) {
        rez[i].resize(n);
        rez[0][i] = s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i, k = 0; k < n; k++, j = (j + 1)%n) {
            rez[k][j] = rez[0][i];
        }
    }
    if (debug) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout <<rez[i][j];
            }
            cout <<endl;
        }
        cout <<endl;
    }

    sort(rez.begin(), rez.end());

    if (debug) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout <<rez[i][j];
            }
            cout <<endl;
        }
        cout <<endl;
    }

    for (int i = 0; i < n; i++) {
        cout <<rez[i][n - 1];
    }
    return 0;
}
