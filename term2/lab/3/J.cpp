//
// Created by covariance on 30.05.2020.
//

#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;

const uint NEUTRAL = 0;
const size_t MAX_SIZE = (1 << 21);

struct pnt {
    uint val;
    uint x;

    explicit pnt(uint x) : val(0), x(x) {}
};

pnt max(pnt a, pnt b) {
    return (a.val > b.val) ? a : b;
}

struct node {
    int upd_add;
    pnt val;

    node() : upd_add(0), val(0) {}
};

node st[2 * MAX_SIZE];

inline void push(size_t v) {
    size_t left = (v << 1);
    size_t right = (v << 1) + 1;

    st[left].upd_add += st[v].upd_add;
    st[left].val.val += st[v].upd_add;
    st[right].upd_add += st[v].upd_add;
    st[right].val.val += st[v].upd_add;
    st[v].upd_add = 0;
}

pnt get(size_t l, size_t r,
        size_t v = 1, size_t cur_l = 0, size_t cur_r = MAX_SIZE - 1) {
    if (l > r) {
        return pnt(0);
    }
    if (l == cur_l && cur_r == r) {
        return st[v].val;
    }
    push(v);
    size_t cur_m = (cur_l + cur_r) >> 1;
    return max(get(l, min(r, cur_m), v << 1, cur_l, cur_m),
               get(max(l, cur_m + 1), r, (v << 1) + 1, cur_m + 1, cur_r));
}

void upd_add(int upd, size_t l, size_t r,
             size_t v = 1, size_t cur_l = 0, size_t cur_r = MAX_SIZE - 1) {
    if (l > r) {
        return;
    }
    if (l == cur_l && cur_r == r) {
        st[v].upd_add += upd;
        st[v].val.val += upd;
        return;
    }
    push(v);
    size_t cur_m = (cur_l + cur_r) >> 1;
    upd_add(upd, l, min(r, cur_m), v << 1, cur_l, cur_m);
    upd_add(upd, max(l, cur_m + 1), r, (v << 1) + 1, cur_m + 1, cur_r);
    st[v].val = max(st[v << 1].val, st[(v << 1) + 1].val);
}

void print() {
    size_t cur_s = 1;
    size_t pos = 1;
    while (cur_s <= MAX_SIZE) {
        for (size_t i = 0; i < cur_s; ++i) {
            cout << '(' << st[pos + i].val.val << ';' << st[pos + i].val.x << ';'
                 << st[pos + i].upd_add << ") ";
        }
        pos += cur_s;
        cur_s *= 2;
        cout << endl;
    }
}

struct recside {
    uint l, r;
    uint x;
    bool open;

    recside() : l(0), r(0), x(0), open(false) {}

    recside(bool open, int a, int b, uint x) : x(x), open(open) {
        l = min((uint) (a + 1e6), (uint) (b + 1e6));
        r = max((uint) (a + 1e6), (uint) (b + 1e6));
    }

    pnt apply() {
        upd_add(this->open ? 1 : -1, this->l, this->r);
        return get(this->l, this->r);
    }
};

int main() {
    for (size_t i = 0; i < MAX_SIZE; i++) {
        st[i + MAX_SIZE].upd_add = 0;
        st[i + MAX_SIZE].val.val = 0;
        st[i + MAX_SIZE].val.x = i;
    }
    for (size_t i = MAX_SIZE - 1; i > 0; i--) {
        st[i].upd_add = 0;
        st[i].val = max(st[i << 1].val, st[(i << 1) + 1].val);
    }

    int a, b, c, d;
    size_t n;
    cin >> n;
    vector<recside> arr(2 * n, recside());
    for (size_t i = 0; i < n; i++) {
        cin >> a >> b >> c >> d;
        arr[2 * i].open = true;
        arr[2 * i].x = (uint) (a + 1e6);
        arr[2 * i + 1].open = false;
        arr[2 * i + 1].x = (uint) (c + 1e6);

        arr[2 * i].r = arr[2 * i + 1].r = (uint) (d + 1e6);
        arr[2 * i].l = arr[2 * i + 1].l = (uint) (b + 1e6);
    }
    sort(arr.begin(), arr.end(),
         [](recside a, recside b) {
             if (a.x == b.x) {
                 if (a.open && b.open) {
                     return a.l < b.l;
                 }
                 return a.open;
             }
             return a.x < b.x;
         });
    pnt best(0), cur(0);
    uint bestx = 0;
    for (auto &rec : arr) {
        cur = rec.apply();
        // cout << "On " << (rec.open ? "opening " : "closing ") << rec.l << ";" << rec.r
        //     << " mxval is " << cur.val << endl;
        if (cur.val > best.val) {
            bestx = rec.x;
            best = cur;
        }
    }
    cout << best.val << endl
         << ((int) bestx - (int) (1e6)) << ' ' << ((int) best.x - (int) (1e6)) << endl;
    return 0;
}
