#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;

bool debug = false;
typedef long long ll;

int main() {
    string templ, s;
    getline(cin, templ);
    getline(cin, s);
    int n = templ.length(), m = s.length();
    vector<vector<bool>> d(n + 1, vector<bool>(m + 1, false));
    d[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (templ[i - 1] == '*') {
                d[i][j] = (j == 0) ? d[i - 1][j] :
                    (d[i - 1][j - 1] || d[i][j - 1] || d[i - 1][j]);
            }
            if (templ[i - 1] == '?') {
                d[i][j] = (j == 0) ? false : d[i - 1][j - 1];
            }
            if (templ[i - 1] != '*' && templ[i - 1] != '?') {
                d[i][j] = (j != 0 && templ[i - 1] == s[j - 1]) ? d[i - 1][j - 1] : false;
            }
        }
    }
    if (d[n][m]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
