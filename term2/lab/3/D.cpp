//
// Created by covariance on 24.05.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

uint MAX_SIZE;
vector<int> st;
int NEUTRAL = (((1 << 30) - 1) << 1) + 1;

void sett(size_t i, int x) {
    i += st.size() / 2;
    st[i] = x;
    i /= 2;
    while (i != 0) {
        st[i] = min(st[i << 1], st[(i << 1) + 1]);
        i /= 2;
    }
}

int get(size_t l, size_t r, size_t v = 1, size_t tl = 0, size_t tr = MAX_SIZE - 1) {
    if (l > r) {
        return NEUTRAL;
    }
    if (l == tl && tr == r) {
        return st[v];
    }
    size_t tm = (tl + tr) >> 1;
    return min(get(l, min(r, tm), v << 1, tl, tm),
               get(max(l, tm + 1), r, (v << 1) + 1, tm + 1, tr));
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    uint n;
    cin >> n;
    MAX_SIZE = 1;
    while (MAX_SIZE < n) {
        MAX_SIZE *= 2;
    }
    st.resize(2 * MAX_SIZE, NEUTRAL);
    int a;
    for (size_t i = 0; i < n; i++) {
        cin >> a;
        sett(i, a);
    }
    string op;
    while (cin >> op) {
        if (op == "min") {
            uint l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << get(l, r) << "\n";
        } else {
            size_t i;
            int x;
            cin >> i >> x;
            sett(i - 1, x);
        }
        // print();
    }
    return 0;
}
