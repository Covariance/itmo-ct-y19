#include <bits/stdc++.h>

using namespace std;

bool debug = false;

int main() {
    if (!debug) {
        freopen("mtf.in", "r", stdin);
        freopen("mtf.out", "w", stdout);
    }
    string s; cin >> s;
    int c[26];
    for (int i = 0; i < 26; i++) {
        c[i] = i;
    }
    for (int i = 0; i < s.length(); i++) {
        int j = 0;
        while (c[j] !=  (int)s[i] - (int)'a') {
            j++;
        }
        cout << j + 1 << ' ';
        int tmp = c[j];
        while (j > 0) {
            c[j] = c[j - 1];
            j--;
        }
        c[0] = tmp;
    }
    return 0;
}
