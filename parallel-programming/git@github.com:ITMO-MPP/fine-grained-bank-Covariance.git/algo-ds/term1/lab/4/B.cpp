#include <bits/stdc++.h>

using namespace std;

bool debug = false;
const int MAX_INT = 2147483647;

int main() {
    if (!debug) {
        freopen("lis.in", "r", stdin);
        freopen("lis.out", "w", stdout);
    }
    int n, maxLength = 0;
    cin >> n;
    int *arr = new int[n];
    int *d = new int[n + 1];
    int *position = new int[n], *previous = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n + 1; i++) {
        d[i] = MAX_INT;
    }
    d[0] = -MAX_INT - 1;
    for (int i = 0; i < n; i++) {
        if (d[n] > arr[i]) {
            int l = 0, r = n;
            while (l < r) {
                int m = (l + r) / 2;
                if (d[m] < arr[i]) {
                    l = m + 1;
                } else {
                    r = m;
                }
            }


            if (l < n + 1) {
                d[l] = arr[i];
                maxLength = max(maxLength, l);
                position[l] = i;
                previous[i] = position[l - 1];
            }
        }
    }
    cout << maxLength << endl;
    int p = position[maxLength];
    int *ans = new int[maxLength];
    for (int i = 0; i < maxLength; i++) {
        ans[i] = arr[p];
        p = previous[p];
    }
    for (int i = 0; i < maxLength; i++) {
        cout << ans[maxLength - i - 1] << " ";
    }
    return 0;
}
