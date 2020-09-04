#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = false;
vector<int> pw;
vector<pair<int, int>> bnd;
vector<int> delta;
vector<int> last;
vector<int> dp;
int mx;
const int MIN_INF = -2140000000;

int main() {
    int n, k;
    if (!debug) {
        freopen("meetings.in", "r", stdin);
        freopen("meetings.out", "w", stdout);
    }
    cin >> n >> k;
    pw.resize(n);
    bnd.resize(n);
    delta.resize(n);
    pw[0] = 1;
    cin >> bnd[0].fs >> bnd[0].sc >> delta[0];
    for (int i = 1; i < n; i++) {
        pw[i] = pw[i - 1] * 2;
        cin >> bnd[i].fs >> bnd[i].sc >> delta[i];
    }
    mx = pw[n - 1] * 2;
    dp.resize(mx, MIN_INF);
    last.resize(mx, -1);
    dp[0] = k;
    int bestAnsCount = 0, bestAnsMask = 0;
    for (int i = 1; i < mx; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if ((i & pw[j]) != 0) {
                cnt++;
                if (bnd[j].fs <= dp[i ^ pw[j]] &&
                    dp[i ^ pw[j]] <= bnd[j].sc) {
                    dp[i] = dp[i ^ pw[j]] + delta[j];
                    last[i] = i ^ pw[j];
                }
            }
        }
        if (cnt > bestAnsCount && dp[i] != MIN_INF) {
            bestAnsMask = i;
            bestAnsCount = cnt;
        }
    }
    cout << bestAnsCount <<endl;
    vector<int> ans;
    while (last[bestAnsMask] != -1) {
        for (int i = 0; i < n; i++) {
            if ((bestAnsMask & pw[i]) != (last[bestAnsMask] & pw[i])) {
                ans.push_back(i + 1);
            }
        }
        bestAnsMask = last[bestAnsMask];
    }
    for (int i = 0; i < bestAnsCount; i++) {
        cout << ans[bestAnsCount - i - 1] << ' ';
    }
    return 0;
}
