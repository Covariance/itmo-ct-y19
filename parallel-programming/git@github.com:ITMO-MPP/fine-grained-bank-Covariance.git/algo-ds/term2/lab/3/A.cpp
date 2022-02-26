//
// Created by covariance on 23.05.2020.
//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

const uint MAX_SIZE = 1 << 24;
const uint NEUTRAL = 0;

uint st[MAX_SIZE];

uint a, b, cur = 0;

unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    uint m, q, ans = 0, l, r, add;
    for (size_t i = 0; i < MAX_SIZE; ++i) {
        st[i] = 0;
    }
    cin >> m >> q;
    cin >> a >> b;
    for (size_t i = 0; i < m; ++i) {
        add = nextRand();
        l = nextRand();
        r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        st[l] += add;
        st[r + 1] -= add;
    }
    for (size_t i = 0; i < MAX_SIZE - 1; ++i) {
        st[i + 1] += st[i];
    }
    for (size_t i = 0; i < MAX_SIZE - 1; ++i) {
        st[i + 1] += st[i];
    }
    for (size_t i = 0; i < q; ++i) {
        l = nextRand();
        r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        ans += (st[r] - st[l - 1]);
    }
    cout << ans;
}
