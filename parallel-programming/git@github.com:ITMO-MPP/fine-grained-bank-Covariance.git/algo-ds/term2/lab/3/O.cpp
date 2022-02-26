//
// Created by covariance on 31.05.2020.
//
#pragma GCC optimize("-Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC target("arch=corei7-avx")

#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;

using namespace std;

const int NEUTRAL = 10000000;
const size_t max_ups = 22;
vector<uint> depth;
vector<vector<size_t>> ups;
vector<vector<int>> mins;
vector<uint> translation;
unordered_map<uint, size_t> back_translation;

vector<uint> shift;

void init() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    shift.resize(500100, 0);
    shift[1] = 0;
    for (size_t i = 2; i < shift.size(); i++) shift[i] = shift[i / 2] + 1;

    depth.resize(0);
    ups.resize(0);
    mins.resize(0);
    translation.resize(0);

    vector<size_t> first_up(max_ups);
    vector<int> first_min(max_ups);
    for (size_t i = 0; i < max_ups; i++) {
        first_up[i] = 0;
        first_min[i] = NEUTRAL;
    }
    mins.push_back(first_min);
    ups.push_back(first_up);
    depth.push_back(0);
    translation.push_back(1);
    back_translation[1] = 0;
}

void fill_ups(size_t par, uint name, int weight) {
    vector<size_t> up(max_ups);
    vector<int> mn(max_ups);
    up[0] = par;
    mn[0] = weight;
    for (size_t i = 1; i < max_ups; i++) {
        up[i] = ups[up[i - 1]][i - 1];
        mn[i] = min(mins[up[i - 1]][i - 1], mn[i - 1]);
    }
    ups.push_back(up);
    mins.push_back(mn);
    depth.push_back(depth[par] + 1);
    translation.push_back(name);
    back_translation[name] = ups.size() - 1;
}

int find_min(size_t v, uint lca_depth) {
    int min_res = NEUTRAL;
    while (depth[v] > lca_depth) {
        min_res = min(min_res, mins[v][shift[depth[v] - lca_depth]]);
        v = ups[v][shift[depth[v] - lca_depth]];
    }
    return min_res;
}

size_t lca(size_t u, size_t v) {
    if (depth[u] != depth[v]) {
        if (depth[u] < depth[v]) swap(u, v);
        while (depth[u] > depth[v]) {
            u = ups[u][shift[depth[u] - depth[v]]];
        }
    }
    size_t step = shift[depth[u]] + 1;

    if (u == v) return depth[u];

    while (step--) {
        if (ups[u][step] != ups[v][step]) {
            u = ups[u][step];
            v = ups[v][step];
        }
    }
    return depth[ups[u][0]];
}

int main() {
    init();
    size_t a, b, k, n;
    int w;
    cin >> n;
    for (size_t i = 0; i < n - 1; i++) {
        cin >> a >> w;
        fill_ups(back_translation[a], i + 2, w);
    }
    cin >> k;
    while (k--) {
        cin >> a >> b;
        uint dpth = lca(back_translation[a], back_translation[b]);
        cout << min(find_min(back_translation[a], dpth),
                    find_min(back_translation[b], dpth)) << "\n";
    }
    return 0;
}
