//
// Created by covariance on 24.05.2020.
//
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;

uint MOD;
uint tmp[4]{};

struct matrix {
    uint val[4]{};

    matrix() {
        for (uint &i : this->val) {
            i = 0;
        }
    }

    explicit matrix(const uint val[4]) {
        for (size_t i = 0; i < 4; ++i) {
            this->val[i] = val[i];
        }
    }

    matrix operator*(const matrix &that) {
        tmp[0] = (this->val[0] * that.val[0] + this->val[1] * that.val[2]) % MOD;
        tmp[1] = (this->val[0] * that.val[1] + this->val[1] * that.val[3]) % MOD;
        tmp[2] = (this->val[2] * that.val[0] + this->val[3] * that.val[2]) % MOD;
        tmp[3] = (this->val[2] * that.val[1] + this->val[3] * that.val[3]) % MOD;
        return matrix(tmp);
    }

    friend istream &operator>>(istream &in, matrix &m) {
        in >> m.val[0] >> m.val[1]
           >> m.val[2] >> m.val[3];
        return in;
    }

    friend ostream &operator<<(ostream &out, const matrix &m) {
        out << m.val[0] << ' ' << m.val[1] << '\n'
            << m.val[2] << ' ' << m.val[3] << '\n';
        return out;
    }
};

matrix NEUTRAL(new uint[4]{1, 0, 0, 1});

size_t MAX_SIZE;
vector<matrix> st;

void sett(size_t i, matrix x) {
    i += st.size() / 2;
    st[i] = x;
    i /= 2;
    while (i != 0) {
        st[i] = st[i << 1] * st[(i << 1) + 1];
        i /= 2;
    }
}

matrix get(size_t l, size_t r, size_t v = 1, size_t tl = 0, size_t tr = MAX_SIZE - 1) {
    if (l > r) {
        return NEUTRAL;
    }
    if (l == tl && tr == r) {
        return st[v];
    }
    size_t tm = (tl + tr) >> 1;
    return get(l, min(r, tm), v << 1, tl, tm) *
           get(max(l, tm + 1), r, (v << 1) + 1, tm + 1, tr);
}


int main() {
    uint n, m;
    cin >> MOD >> n >> m;
    MAX_SIZE = 1;
    while (MAX_SIZE < n) {
        MAX_SIZE *= 2;
    }
    st.resize(2 * MAX_SIZE);
    matrix tm;
    for (size_t i = 0; i < n; i++) {
        cin >> tm;
        sett(i, tm);
    }
    for (size_t i = 0; i < m; i++) {
        size_t l = 0, r = 0;
        cin >> l >> r;
        l--;
        r--;
        cout << get(l, r) << '\n';
    }
    return 0;
}
