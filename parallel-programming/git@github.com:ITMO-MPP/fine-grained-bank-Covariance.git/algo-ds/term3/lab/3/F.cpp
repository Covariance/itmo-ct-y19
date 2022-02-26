//
// Created by covariance on 17.11.2020.
//
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, gr;
vector<int> match, top, comps;
vector<bool> used;

void top_sort(int v) {
    if (used[v]) {
        return;
    }
    used[v] = true;

    for (int son : g[v]) {
        top_sort(son);
    }

    top.push_back(v);
}

void dfs(int v, int comp) {
    if (used[v]) {
        return;
    }
    used[v] = true;
    comps[v] = comp;
    for (int son : gr[v]) {
        dfs(son, comp);
    }
}

void add_edge(int from, int to) {
    g[from].push_back(to);
    gr[to].push_back(from);
}

void erase_if_present(vector<int> &vec, int val) {
    auto it = find(vec.begin(), vec.end(), val);
    if (it != vec.end()) {
        vec.erase(it);
    }
}

int main() {
    int n, tmp, to;
    cin >> n;

    g.resize(2 * n);
    gr.resize(2 * n);

    for (int i = 0; i != n; ++i) {
        cin >> tmp;
        for (int j = 0; j != tmp; ++j) {
            cin >> to;
            add_edge(n + to - 1, i);
        }
    }

    for (int i = 0; i != n; ++i) {
        cin >> tmp;
        add_edge(i, n + tmp - 1);
        erase_if_present(g[n + tmp - 1], i);
        erase_if_present(gr[i], n + tmp - 1);
    }

    used.assign(2 * n, false);
    for (int i = 0; i != 2 * n; ++i) {
        top_sort(i);
    }
    reverse(top.begin(), top.end());

    comps.resize(2 * n);
    used.assign(2 * n, false);

    int cur_comp = 0;
    for (int &i : top) {
        dfs(i, ++cur_comp);
    }

    for (int i = 0; i != n; ++i) {
        vector<int> marriage;
        for (int couple : gr[i]) {
            if (comps[couple] == comps[i]) {
                marriage.push_back(couple);
            }
        }

        cout << marriage.size() + 1 << ' ' << g[i][0] - n + 1;
        for (int couple : marriage) {
            cout << ' ' << couple - n + 1;
        }
        cout << endl;
    }
    return 0;
}
