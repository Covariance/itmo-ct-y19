#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

int a, b, n;
ll k, ans = 0;
vector<ll> arr;
vector<ll> tmp;


uint cur = 0;
uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

int nextRand32() {
    uint a = nextRand24(), b = nextRand24();
    return (int)((a << 8)^b);
}

ll get(int i, int j) {
    return (i == 0) ? (arr[j - 1]) : (arr[j - 1] - arr[i - 1]);
}

void read() {
    cin >> n >> k >> a >> b;
    if (n == 1) {
        cout <<((nextRand24() >= k) ? 1 : 0);
        exit(0);
    }
    ans = ((ll) n * (ll)(n + 1)) >> 1;
    arr.resize(n + 1);
    tmp.resize(n + 1);
    arr[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        arr[i] = nextRand32();
        arr[i] += arr[i - 1];
    }
}

void subarrays(int l, int r) {
    if (l != r) {
        int mid = (l + r) / 2;
        subarrays(l, mid);
        subarrays(mid + 1, r);

        int i = l, j = mid + 1;
        while (i <= mid && j <= r) {
            if (arr[j] < k + arr[i]) {
                ans -= (mid - i + 1);
                j++;
            } else {
                i++;
            }
        }

        i = l;
        j = mid + 1;
        for (int k = 0; i <= mid || j <= r; k++) {
            if (i <= mid && j <= r) {
                if (arr[i] <= arr[j]) {
                    tmp[k] = arr[i++];
                } else {
                    tmp[k] = arr[j++];
                }
            } else if (i <= mid) {
                tmp[k] = arr[i++];
            } else {
                tmp[k] = arr[j++];
            }
        }

        for (int i = l; i <= r; i++) {
            arr[i] = tmp[i - l];
        }
    }
}

int main() {
    read();
    subarrays(0, n);
    cout << ans;
    return 0;
}
