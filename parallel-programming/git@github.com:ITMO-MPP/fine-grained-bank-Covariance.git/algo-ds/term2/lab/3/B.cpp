//
// Created by covariance on 23.05.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

size_t n;
size_t pw[20];
vector<size_t> shift;
vector<vector<uint>> sparse;
uint cur;

size_t get(size_t i) {
    return min(i, n - 1);
}

uint ans;

int main() {
    n = 1;
    for (size_t &i : pw) {
        i = n;
        n *= 2;
    }
    uint u, v;
    size_t m;
    cin >> n >> m;
    shift.resize(n + 1, 0);
    vector<int> arr(n + 1);
    sparse.resize(n + 1, vector<uint>(21, 0));
    cin >> sparse[1][0] >> u >> v;
    for (size_t i = 2; i <= n; i++) {
        sparse[i][0] = (23 * sparse[i - 1][0] + 21563) % 16714589;
        shift[i] = shift[i / 2] + 1;
    }
    for (size_t j = 1; j <= 21; j++) {
        for (size_t i = 1; i <= n; i++) {
            if (j > shift[n - i + 1]) {
                break;
            }
            sparse[i][j] = min(sparse[i][j - 1], sparse[i + pw[j - 1]][j - 1]);
        }
    }
    for (size_t i = 0; i < m; i++) {
        size_t l = min(u, v), r = max(u, v);
        size_t seg = shift[r - l + 1];
        ans = min(sparse[l][seg], sparse[r - pw[seg] + 1][seg]);
        if (i + 1 != m) {
            u = ((17 * u + 751 + ans + 2 * (i + 1)) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * (i + 1)) % n) + 1;
        }
    }
    cout << u << " " << v << " " << ans;
    return 0;
}
