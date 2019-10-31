#include <bits/stdc++.h>

using namespace std;

bool debug = false;

int main() {
    if (!debug) {
        freopen("lzw.in", "r", stdin);
        freopen("lzw.out", "w", stdout);
    }
    string s; cin >> s;
    vector<string> dict;
    string t = "";
    for (int i = 0; i < 26; i++) dict.push_back(string(1, char('a' + i)));
    for (int i = 0; i < s.length(); i++) {
        string tmp = t + string(1, s[i]);
        int j;
        for (j = 0; j < dict.size(); j++) {
            if (tmp == dict[j]) {
                break;
            }
        }

        if (j < dict.size()) {
            t = tmp;
        } else {
            for (j = 0; j < dict.size(); j++) {
                if (t == dict[j]) {
                    cout << j <<' ';
                    break;
                }
            }
            dict.push_back(tmp);
            t = string(1, s[i]);
        }
    }
    for (int i = 0; i < dict.size(); i++) {
                if (t == dict[i]) {
                    cout << i <<' ';
                    break;
                }
            }
    return 0;
}
