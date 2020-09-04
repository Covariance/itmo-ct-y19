//
// Created by covariance on 30.05.2020.
//

//
// Created by covariance on 23.05.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

struct pnt {
    uint val;
    size_t vert;

    pnt() : val(0), vert(0) {}

    pnt(uint val, size_t vert) : val(val), vert(vert) {}
};

pnt min(pnt a, pnt b) {
    return (a.val < b.val) ? a : b;
}

size_t n;
size_t pw[20];
vector<size_t> shift;
vector<vector<pnt>> sparse;

vector<vector<uint>> g;
vector<uint> inclusion;
vector<pnt> arr;
uint cnt = 0;

void dfs(uint depth, size_t v) {
    inclusion[v] = cnt;
    arr.emplace_back(depth, v);
    cnt++;
    for (auto &son : g[v]) {
        dfs(depth + 1, son);
        arr.emplace_back(depth, v);
        cnt++;
    }
}

int main() {
    n = 1;
    for (size_t &i : pw) {
        i = n;
        n *= 2;
    }
    uint u;
    size_t gsize, m;
    cin >> gsize >> m;
    g.resize(gsize, vector<uint>(0));
    for (size_t i = 0; i < gsize - 1; i++) {
        cin >> u;
        g[u].push_back(i + 1);
    }
    inclusion.resize(gsize);
    dfs(0, 0);

    n = arr.size();
    shift.resize(n + 1, 0);
    sparse.resize(n + 1, vector<pnt>(22));
    for (size_t i = 2; i <= n; i++) shift[i] = shift[i / 2] + 1;
    for (size_t i = 1; i <= n; i++) sparse[i][0] = arr[i];

    for (size_t j = 1; j <= 21; j++) {
        for (size_t i = 1; i <= n; i++) {
            if (j > shift[n - i + 1]) {
                break;
            }
            sparse[i][j] = min(sparse[i][j - 1], sparse[i + pw[j - 1]][j - 1]);
        }
    }

    ull x, y, z;
    ull a1, a2, a3;
    size_t ans = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    ull sum = 0;
    for (size_t i = 0; i < m; i++) {
        size_t f = inclusion[((size_t) a1 + ans) % gsize], s = inclusion[(size_t) a2];
        size_t l = min(f, s), r = max(f, s);
        size_t seg = shift[r - l + 1];
        ans = min(sparse[l][seg], sparse[r - pw[seg] + 1][seg]).vert;
        sum += ans;
        for (size_t j = 0; j < 2; j++) {
            a3 = (x * a1 + y * a2 + z) % gsize;
            a1 = a2;
            a2 = a3;
        }
    }
    cout << sum;
    return 0;
}
