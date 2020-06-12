//
// Created by covariance on 06.06.2020.
//
#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

int main() {
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);

    unordered_map<char, vector<pair<char, char>>> unfolding; // unfolding[FROM NODE] = { [LEFT NODE][RIGHT NODE] }
    unordered_map<char, unordered_map<char, int>> terminal; // terminal[FROM NODE][ENDING SYMBOL] = COUNT OF ENDINGS

    for (char i = 'A'; i <= 'Z'; i++) {
        unfolding[i] = vector<pair<char, char>>(0);
        for (char j = 'a'; j <= 'z'; j++) {
            terminal[i][j] = 0;
        }
    }

    size_t n;
    char start;
    cin >> n >> start;
    string s;
    getline(cin, s);
    for (size_t i = 0; i < n; i++) {
        getline(cin, s);
        char from = s[0];
        if ('A' <= s[5] && s[5] <= 'Z') {
            unfolding[from].emplace_back(s[5], s[6]);
        } else {
            terminal[from][s[5]]++;
        }
    }

    cin >> s;
    size_t length = s.length();

    // dp[LEFT BORDER][RIGHT BORDER][BEGIN FROM]
    vector<vector<unordered_map<char, size_t>>>
            dp(length, vector<unordered_map<char, size_t>>(length, unordered_map<char, size_t>()));

    for (size_t i = 0; i < length; i++)
        for (size_t j = 0; j < length; j++)
            for (char k = 'A'; k <= 'Z'; k++)
                dp[i][j][k] = 0;

    for (size_t i = 0; i < length; i++)
        for (char j = 'A'; j <= 'Z'; j++)
            dp[i][i][j] += terminal[j][s[i]];

    for (size_t len = 1; len < length; len++)
        for (size_t left = 0; left < length - len; left++)
            for (size_t splitter = left; splitter < left + len; splitter++)
                for (char c = 'A'; c <= 'Z'; c++)
                    for (auto &unf : unfolding[c])
                        dp[left][left + len][c] =
                                (1ll * dp[left][splitter][unf.first] *
                                 dp[splitter + 1][left + len][unf.second] +
                                 dp[left][left + len][c]) % mod;


    cout << dp[0][length - 1][start];
    return 0;
}