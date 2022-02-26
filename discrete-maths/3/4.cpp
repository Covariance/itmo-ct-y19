#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool debug = false;

int main() {
    if (!debug) {
        freopen("chaincode.in", "r", stdin);
        freopen("chaincode.out", "w", stdout);
    }
    int n;
    cin >> n;
    map<string, bool> codes;

    for(int i = 0; i < 1 << n; i++) {
        codes[to_string(i)] = false;
    }

    string cur (n, '0');
    string pref, opt1, opt0;
    codes[cur] = true;
    cout << cur <<"\n";
    while (true) {
        opt1 = cur.substr(1).append("1");
        if (!codes[opt1]) {
            cur = opt1;
        } else {
            opt0 = cur.substr(1).append("0");
            if (!codes[opt0]) {
                cur = opt0;
            } else {
                break;
            }
        }
        codes[cur] = true;
        cout << cur <<"\n";
    }
    return 0;
}
