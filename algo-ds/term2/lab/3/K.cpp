//
// Created by covariance on 30.05.2020.
//

#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;

using namespace std;

const size_t max_ups = 22;
vector<uint> depth;
vector<vector<size_t>> ups;
vector<uint> translation;
unordered_map<uint, size_t> back_translation;

vector<uint> shift;

void init() {
    shift.resize(500100, 0);
    shift[1] = 0;
    for (size_t i = 2; i < shift.size(); i++) shift[i] = shift[i / 2] + 1;

    depth.resize(0);
    ups.resize(0);
    translation.resize(0);

    vector<size_t> first_up(max_ups);
    for (size_t i = 0; i < max_ups; i++) first_up[i] = 0;
    ups.push_back(first_up);
    depth.push_back(0);
    translation.push_back(1);
    back_translation[1] = 0;
}

void fill_ups(size_t par, uint name) {
    vector<size_t> up(max_ups);
    up[0] = par;
    for (size_t i = 1; i < max_ups; i++) up[i] = ups[up[i - 1]][i - 1];
    ups.push_back(up);
    depth.push_back(depth[par] + 1);
    translation.push_back(name);
    back_translation[name] = ups.size() - 1;
}

size_t lca(size_t u, size_t v) {
    if (depth[u] != depth[v]) {
        if (depth[u] < depth[v]) swap(u, v);
        while (depth[u] > depth[v]) {
            u = ups[u][shift[depth[u] - depth[v]]];
        }
    }
    size_t step = shift[depth[u]] + 1;

    if (u == v) return u;

    while (step--) {
        if (ups[u][step] != ups[v][step]) {
            u = ups[u][step];
            v = ups[v][step];
        }
    }
    return ups[u][0];
}

int main() {
    init();

    size_t a, b, k;
    cin >> k;
    string command;
    while (k--) {
        cin >> command >> a >> b;
        if (command == "ADD") {
            fill_ups(back_translation[a], b);
        }
        if (command == "GET") {
            cout << translation[lca(back_translation[a], back_translation[b])] << "\n";
        }
    }
    return 0;
}
