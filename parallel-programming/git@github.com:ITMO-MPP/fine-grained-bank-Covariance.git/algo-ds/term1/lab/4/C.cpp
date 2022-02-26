#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = false;
typedef long long ll;
size_t n;
const ll MAXLL = (1ll << 62);
vector<vector<ll>> d;
vector<vector<size_t>> di;
vector<bool> ansBuilder;
vector<ll> freq;

ll getFreq(size_t l, size_t r) {
    if (l == 0) return freq[r];
    return freq[r] - freq[l - 1];
}

void getAns(size_t l, size_t r, size_t ansLength) {
    if (l == r) {
        for (size_t i = 0; i < ansLength; i++) {
            cout << ((ansBuilder[i]) ? "1" : "0");
        }
        cout << endl;
    } else {
        ansBuilder.push_back(false);
        getAns(l, di[l][r], ansLength + 1);
        ansBuilder.pop_back();
        ansBuilder.push_back(true);
        getAns(di[l][r] + 1, r, ansLength + 1);
        ansBuilder.pop_back();
    }
}

int main() {
    if (!debug) {
        freopen("optimalcode.in", "r", stdin);
        freopen("optimalcode.out", "w", stdout);
    }
    cin >> n;
    di.resize(n);
    d.resize(n);
    freq.resize(n);
    for (size_t i = 0; i < n; i++) {
        cin >> freq[i];
        freq[i] += (i == 0) ? 0 : freq[i - 1];
        di[i].resize(n, -1);
        d[i].resize(n, MAXLL);
        d[i][i] = 0;
        di[i][i] = i;
    }
    for (size_t len = 1; len < n; len++) {
        for (size_t i = 0; i + len < n; i++) {
            for (size_t dv = di[i][i + len - 1]; dv <= min(di[i + 1][i + len], n - 2); dv++) {
                if (d[i][i + len] >= d[i][dv] + d[dv + 1][i + len] + getFreq(i, i + len)) {
                    d[i][i + len] = d[i][dv] + d[dv + 1][i + len] + getFreq(i, i + len);
                    di[i][i + len] = dv;
                }
            }
        }
    }
    cout << d[0][n - 1] << endl;
    getAns(0, n - 1, 0);
    return 0;
}
