#include <bits/stdc++.h>

using namespace std;
typedef long double ld;
int n;
ld a;

pair<bool, ld> check(ld a0, ld a1) {
    ld tmp;
    bool retv = true;
    for (int i = 2; i < n; i++) {
        tmp = a1;
        a1 = 2*(a1 + 1) - a0;
        a0 = tmp;
        if (a1 <= 0) retv = false;
    }
    return make_pair(retv, a1);
}

int main() {
    cin >> n >> a;
    ld l = 0, mid, r = a;
    pair<bool, ld> is_ok;
    for (int i = 0; i < 1000; i++) {
        mid = (l + r) / 2;
        is_ok = check(a, mid);
        if (is_ok.first) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout.precision(20);
    cout << is_ok.second;
    return 0;
}
