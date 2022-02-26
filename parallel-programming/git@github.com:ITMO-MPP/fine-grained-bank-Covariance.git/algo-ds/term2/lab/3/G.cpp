//
// Created by covariance on 24.05.2020.
//
#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;

const ll NEUTRAL = 9223372036854775807LL;


struct node {
    ll upd_add;
    ll upd_over;
    bool is_over;

    ll val;

    explicit node(ll x)
            : upd_add(0), upd_over(0), is_over(false), val(x) {}

    node() : node(NEUTRAL) {}

    node(node a, node b) : node(min(a.val, b.val)) {}
};

size_t MAX_SIZE;
vector<node> st;


inline void push(size_t v) {
    size_t left = (v << 1);
    size_t right = (v << 1) + 1;
    if (st[v].is_over) {
        st[left].is_over = true;
        st[left].upd_add = st[v].upd_add;
        st[left].upd_over = st[v].upd_over;
        st[left].val = st[v].upd_over + st[v].upd_add;

        st[right].is_over = true;
        st[right].upd_add = st[v].upd_add;
        st[right].upd_over = st[v].upd_over;
        st[right].val = st[v].upd_over + st[v].upd_add;

        st[v].is_over = false;
        st[v].upd_add = 0;
    } else {
        st[left].upd_add += st[v].upd_add;
        st[left].val += st[v].upd_add;
        st[right].upd_add += st[v].upd_add;
        st[right].val += st[v].upd_add;
        st[v].upd_add = 0;
    }
}

ll get(size_t l, size_t r,
       size_t v = 1, size_t cur_l = 0, size_t cur_r = MAX_SIZE - 1) {
    if (l > r) {
        return NEUTRAL;
    }
    if (l == cur_l && cur_r == r) {
        return st[v].val;
    }
    push(v);
    size_t cur_m = (cur_l + cur_r) >> 1;
    return min(get(l, min(r, cur_m), v << 1, cur_l, cur_m),
               get(max(l, cur_m + 1), r, (v << 1) + 1, cur_m + 1, cur_r));
}

void upd_add(ll upd, size_t l, size_t r,
             size_t v = 1, size_t cur_l = 0, size_t cur_r = MAX_SIZE - 1) {
    if (l > r) {
        return;
    }
    if (l == cur_l && cur_r == r) {
        st[v].upd_add += upd;
        st[v].val += upd;
        return;
    }
    push(v);
    size_t cur_m = (cur_l + cur_r) >> 1;
    upd_add(upd, l, min(r, cur_m), v << 1, cur_l, cur_m);
    upd_add(upd, max(l, cur_m + 1), r, (v << 1) + 1, cur_m + 1, cur_r);
    st[v].val = min(st[v << 1].val, st[(v << 1) + 1].val);
}

void upd_over(ll over, size_t l, size_t r,
              size_t v = 1, size_t cur_l = 0, size_t cur_r = MAX_SIZE - 1) {
    if (l > r) {
        return;
    }
    if (l == cur_l && cur_r == r) {
        st[v].val = over;
        st[v].is_over = true;
        st[v].upd_add = 0;
        st[v].upd_over = over;
        return;
    }
    push(v);
    size_t cur_m = (cur_l + cur_r) >> 1;
    upd_over(over, l, min(r, cur_m), v << 1, cur_l, cur_m);
    upd_over(over, max(l, cur_m + 1), r, (v << 1) + 1, cur_m + 1, cur_r);
    st[v].val = min(st[v << 1].val, st[(v << 1) + 1].val);
}

void print() {
    size_t cur_s = 1;
    size_t pos = 1;
    while (cur_s <= MAX_SIZE) {
        for (size_t i = 0; i < cur_s; ++i) {
            cout << '(' << st[pos + i].val << ';' << st[pos + i].upd_add << ';'
                 << st[pos + i].is_over << ';' << st[pos + i].upd_over << ") ";
        }
        pos += cur_s;
        cur_s *= 2;
        cout << endl;
    }
}

int main() {
    size_t n, l, r;
    ll change;
    cin >> n;
    MAX_SIZE = 1;
    while (MAX_SIZE < n) {
        MAX_SIZE *= 2;
    }
    st.resize(2 * MAX_SIZE);
    size_t i;
    for (i = 0; i < n; i++) {
        cin >> st[i + MAX_SIZE].val;
        st[i + MAX_SIZE].is_over = false;
        st[i + MAX_SIZE].upd_add = 0;
    }
    for (; i < MAX_SIZE; i++) {
        st[i + MAX_SIZE].val = NEUTRAL;
        st[i + MAX_SIZE].is_over = false;
        st[i + MAX_SIZE].upd_add = 0;
    }
    for (i = MAX_SIZE - 1; i > 0; i--) {
        st[i].val = min(st[i << 1].val, st[(i << 1) + 1].val);
        st[i].is_over = false;
        st[i].upd_add = 0;
    }
    string command;
    while (cin >> command >> l >> r) {
        l--;
        r--;
        if (command == "set") {
            cin >> change;
            upd_over(change, l, r);
        }
        if (command == "add") {
            cin >> change;
            upd_add(change, l, r);
        }
        if (command == "min") {
            cout << get(l, r) << "\n";
        }
    }
}
