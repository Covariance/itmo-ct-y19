#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;
bool debug = false;

const int mod = 1e9;

void javaMod(int* a) {
    *a = (*a < 0 ? (*a + ((abs(*a) + mod - 1) / mod) * mod) : *a) % mod;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    vector<vector<int>> d(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        d[i][i] = 1;
    }
    for (int len = 1; len < n; ++len) {
        for (int l = 0; l + len < n; l++) {
            d[l][l + len] = d[l + 1][l + len] + d[l][l + len - 1];
            d[l][l + len] -= d[l + 1][l + len - 1];
            javaMod(&d[l][l + len]);
            if (arr[l] == arr[l + len]) {
                d[l][l + len] += d[l + 1][l + len - 1] + 1;
                javaMod(&d[l][l + len]);
            }
            if (debug) {
                cout << d[l][l + len] << endl;
            }
        }
    }
    cout << d[0][n - 1] << endl;
    return 0;
}
