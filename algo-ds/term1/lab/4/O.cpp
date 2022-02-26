#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = false;

int x, y, a, b, l;
vector<vector<int>> d;

void clearDyn() {
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            d[i][j] = -1;
        }
    }
    d[0][0] = 0;
}

bool isPossible(int width) {
    clearDyn();
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            if (d[i][j] != -1) {
                for (int deltai = 0; deltai + i <= x; deltai++) {
                    int deltaj = max(0, (width - deltai * a + (b - 1)) / b);
                    if (deltai * a + deltaj * b >= width && deltaj + j <= y) {
                        d[i + deltai][j + deltaj] = max(d[i + deltai][j + deltaj], d[i][j] + 1);
                        if (d[i + deltai][j + deltaj] == l) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    if (!debug) {
        freopen("bridge.in", "r", stdin);
        freopen("bridge.out", "w", stdout);
    }
    cin >> x >> a >> y >> b >> l;
    d.resize(x + 1, vector<int>(y + 1, -1));
    int l = 0, r = (x * a + y * b) + 1;
    while (l + 1 < r) {
        int m = l + (r - l) / 2;
        if (debug) {
            cout << m << endl;
        }
        if (isPossible(m)) {
            l = m;
        } else {
            r = m;
        }
        if (debug) {
            for (int i = 0; i <= x; i++) {
                for (int j = 0; j <= y; j++) {
                    cout << d[i][j] <<' ';
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    cout << l;
    return 0;
}
