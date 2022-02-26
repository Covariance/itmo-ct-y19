#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;

int main() {
    int n, x;
    cin >> n >> x;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int l = 0, m, r = 1;

    while (arr[r - 1] < x && r < n) {
        r*=2;
    }
    if (r >= n) {
        r = n;
    }

    l = r/2;

    while (l + 1 < r) {
        m = (l + r)/2;
        if (arr[m] > x) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << l + 1;
    return 0;
}
