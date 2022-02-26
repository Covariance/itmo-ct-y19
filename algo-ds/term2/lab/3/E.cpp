//
// Created by covariance on 24.05.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;

ll NEUTRAL = 0;

struct segment_tree {
    size_t size;
    vector<ll> st;

    explicit segment_tree(size_t n, vector<ll> vals) {
        size = 1;
        while (size < n) size *= 2;
        st.resize(2 * size, NEUTRAL);
        for (size_t i = 0; i < vals.size(); i++) st[i + size] = vals[i];
        for (size_t i = size - 1; i > 0; i--) st[i] = st[i << 1] + st[(i << 1) + 1];
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
        return get_rec(l, min(r, tm), v << 1, tl, tm) +
               get_rec(max(l, tm + 1), r, (v << 1) + 1, tm + 1, tr);
    }

    void set(size_t i, ll x) {
        i += st.size() / 2;
        st[i] = x;
        i /= 2;
        while (i != 0) {
            st[i] = st[i << 1] + st[(i << 1) + 1];
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<ll> vals(n);
    for (size_t i = 0; i < n; i++) {
        cin >> vals[i];
    }
    segment_tree st(n, vals);
    string op;
    while (cin >> op) {
        if (op == "sum") {
            uint l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << st.get(l, r) << endl;
        } else {
            size_t i;
            ll x;
            cin >> i >> x;
            st.set(i - 1, x);
        }
        // print();
    }
    return 0;
}
