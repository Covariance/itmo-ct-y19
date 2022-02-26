//
// Created by covariance on 31.05.2020.
//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;

ll NEUTRAL = 0;

struct segment_tree {
    size_t size;
    vector<ll> st;

    explicit segment_tree(size_t n) {
        size = 1;
        while (size < n) size *= 2;
        st.resize(2 * size, NEUTRAL);
    }

    ll get(size_t l, size_t r) {
        return get_rec(l, r, 1, 0, this->size - 1);
    }

    ll get_rec(size_t l, size_t r, size_t v, size_t tl, size_t tr) {
        if (l > r) {
            return NEUTRAL;
        }
        if (l == tl && tr == r) {
            return st[v];
        }
        size_t tm = (tl + tr) >> 1;
        return max(get_rec(l, min(r, tm), v << 1, tl, tm),
               get_rec(max(l, tm + 1), r, (v << 1) + 1, tm + 1, tr));
    }

    void set(size_t i, ll x) {
        i += st.size() / 2;
        st[i] += x;
        i /= 2;
        while (i != 0) {
            st[i] = max(st[i << 1], st[(i << 1) + 1]);
            i /= 2;
        }
    }

    void print() {
        size_t cur_s = 1;
        size_t pos = 1;
        while (cur_s <= st.size() / 2) {
            for (size_t i = 0; i < cur_s; ++i) {
                cout << st[pos + i] << " ";
            }
            pos += cur_s;
            cur_s *= 2;
            cout << endl;
        }
    }
};

vector<vector<size_t>> graph;

void dfs() {

}