//
// Created by covariance on 12.06.2020.
//
#include <bits/stdc++.h>

#pragma GCC optimize("-Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC target("arch=corei7-avx")
#pragma GCC optimization ("unroll-loops")

using namespace std;

int main() {
    freopen("cf.in", "r", stdin);
    freopen("cf.out", "w", stdout);
    cout.tie(nullptr);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    size_t n;
    char start;
    string s;
    vector<char> tmp;
    vector<pair<char, vector<char>>> rules;
    unordered_map<char, bool> eps;

    for (char i = 'A'; i <= 'Z'; i++) eps[i] = false;

    cin >> n >> start;
    getline(cin, s);

    for (int i = 0; i < n; i++) {
        getline(cin, s);
        tmp.clear();
        for (int j = 5; j < s.size(); j++) tmp.push_back(s[j]);


        if (tmp.empty()) eps[s[0]] = true;
        else rules.emplace_back(s[0], tmp);
    }
    cin >> s;
    n = s.size();
    size_t rule_cnt = rules.size();
    unordered_map<char, vector<vector<bool>>> dp;
    for (char i = 'A'; i <= 'Z'; i++)
        dp[i] = vector<vector<bool>>(n + 1, vector<bool>(n + 1, false));

    vector<vector<vector<vector<bool>>>> h(rule_cnt);

    for (int i = 0; i < rule_cnt; i++) {
        h[i].resize(n + 1, vector<vector<bool>>(n + 1, vector<bool>(rules[i].second.size() + 1)));
        for (int j = 0; j <= n; j++) {
            h[i][j][j][0] = true;
        }
    }

    for (int i = 0; i <= n; i++) for (char j = 'A'; j <= 'Z'; j++) if (eps[j]) dp[j][i][i] = true;

    for (int i = 0; i < n; i++)
        for (auto &rule : rules)
            if (rule.second.size() == 1 && rule.second[0] == s[i])
                dp[rule.first][i][i + 1] = true;


    for (size_t len = 0; len <= n; len++) {
        for (size_t left = 0; left + len <= n; left++) {
            for (size_t iter = 0, r = left + len; iter < 10; iter++) {
                for (size_t i = 0; i < rule_cnt; i++) {
                    for (auto[rule, k] = tuple{rules[i], (size_t) 1};
                         k <= rule.second.size(); k++) {
                        if (h[i][left][r][k]) continue;
                        bool flag = false;
                        for (int j = left; j <= r; j++) {
                            flag |= ('A' <= rule.second[k - 1] && rule.second[k - 1] <= 'Z')
                                    ?
                                    (h[i][left][j][k - 1] &&
                                     dp[rule.second[k - 1]][j][r]) : (
                                            h[i][left][j][k - 1] && r - j == 1 &&
                                            s[j] == rule.second[k - 1]);
                        }
                        if (flag) h[i][left][r][k] = true;
                    }
                }

                for (int i = 0; i < rule_cnt; i++)
                    if (h[i][left][r][rules[i].second.size()])
                        dp[rules[i].first][left][r] = true;
            }
        }
    }

    cout << (dp[start][0][n] ? "yes" : "no");
    return 0;
}
