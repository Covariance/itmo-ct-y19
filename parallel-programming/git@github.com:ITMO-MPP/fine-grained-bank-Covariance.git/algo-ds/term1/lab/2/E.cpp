#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s;
    vector<string> tmp;
    for (int i = 0; i < n; i++) {
        s.push_back("");
        tmp.push_back("");
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<int> cnt[26];
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cnt[(unsigned int)(s[j][m - i - 1]) - (unsigned int)'a'].push_back(j);
        }
        int curPos = 0;
        for (uint j = 0; j < 26; j++) {
            for (uint k = 0; k < cnt[j].size(); k++) {
                tmp[curPos] = s[cnt[j][k]];
                curPos++;
            }
            cnt[j].clear();
        }
        for (int j = 0; j < n; j++) {
            s[j] = tmp[j];
        }
    }
    for (int i = 0; i < n; i++) {
        cout <<s[i] <<endl;
    }
    return 0;
}
