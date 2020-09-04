//
// Created by covariance on 25.05.2020.
//
#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;


size_t MAX_SIZE;
const int NEUTRAL = (int) (1e9 + 100);

vector<int> st;

void sett(size_t i, int x) {
    i += MAX_SIZE - 1;
    st[i] = x;
    i /= 2;
    while (i != 0) {
        st[i] = min(st[i << 1], st[(i << 1) + 1]);
        i /= 2;
    }
}

int park(size_t l, size_t r) {
    int ans = NEUTRAL;
    l += MAX_SIZE - 1;
    r += MAX_SIZE - 1;
    while (l <= r) {
        if (l & 1) ans = std::min(ans, st[l]);
        if (!(r & 1)) ans = std::min(ans, st[r]);
        l = (l + 1) >> 1;
        r = (r - 1) >> 1;
    }
    return ans;
}

int main() {
    size_t l, n, m;
    std::cin >> n >> m;

    MAX_SIZE = 1;
    while (MAX_SIZE < n) {
        MAX_SIZE <<= 1;
    }
    st.resize(2 * MAX_SIZE, NEUTRAL);

    for (size_t i = 0; i < n; i++) {
        sett(i + 1, i + 1);
    }

    string command;
    while (cin >> command >> l) {
        if (command == "enter") {
            int ans = park(l, n);
            if (ans == NEUTRAL) {
                ans = st[1];
            }
            sett(ans, NEUTRAL);
            cout << ans << "\n";
        }
        if (command == "exit") {
            sett(l, l);
        }
    }
}
