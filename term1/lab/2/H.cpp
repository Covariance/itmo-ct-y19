#include <bits/stdc++.h>

using namespace std;
typedef unsigned int uint;

uint cur = 0, a, b, n, m;
vector<uint> arr;
vector<uint> tmp;

uint nextRand24() {
    cur = cur * a + b;
    return (cur >> 8) % m;
}

unsigned long long inversions(int l, int r) {
    if (l + 1 == r) return 0;
    unsigned long long retVal = inversions(l, (l + r) / 2) + inversions((l + r) / 2, r);
    int lp = l, rp = (l + r) / 2;
    for (int i = l; i < r; i++) {
        if (lp < (l + r) / 2) {
            if (rp < r) {
                if (arr[lp] <= arr[rp]) {
                    tmp[i] = arr[lp];
                    lp++;
                } else {
                    tmp[i] = arr[rp];
                    rp++;
                    retVal += (l + r) / 2 - lp;
                }
            } else {
                tmp[i] = arr[lp];
                lp++;
            }
        } else {
            tmp[i] = arr[rp];
            rp++;
        }
    }
    for (int i = l; i < r; i++) {
        arr[i] = tmp[i];
    }
    return retVal;
}

int main() {
    int n;
    cin >> n >> m >> a >> b;
    for (int i = 0; i < n; i++) {
        arr.push_back(nextRand24());
        tmp.push_back(0);
    }
    cout <<inversions(0, n) <<endl;
    return 0;
}
