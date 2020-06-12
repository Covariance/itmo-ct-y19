//
// Created by covariance on 07.06.2020.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("useless.in", "r", stdin);
    freopen("useless.out", "w", stdout);
    size_t n;
    char start;
    cin >> n >> start;
    string s;

    vector<char> tmp;
    unordered_set<char> present;
    unordered_map<char, vector<vector<char>>> unfolding;
    unordered_map<char, bool> terminal, visited, ans;
    queue<char> q;

    for (char i = 'A'; i <= 'Z'; i++) {
        unfolding[i] = vector<vector<char>>();
        terminal[i] = false;
        visited[i] = false;
        ans[i] = false;
    }

    visited[start] = true;
    present.insert(start);

    getline(cin, s);
    for (size_t i = 0; i < n; i++) {
        tmp.clear();
        getline(cin, s);
        present.insert(s[0]);
        for (size_t j = 5; j < s.size(); j++)
            if ('A' <= s[j] && s[j] <= 'Z') {
                present.insert(s[j]);
                tmp.push_back(s[j]);
            }

        if (!tmp.empty()) unfolding[s[0]].push_back(tmp);
        else terminal[s[0]] = true;

    }

    q.push(start);

    while (!q.empty()) {
        char v = q.front();
        q.pop();
        for (auto &i : unfolding[v]) {
            for (auto to : i) {
                if (!visited[to]) {
                    visited[to] = true;
                    q.push(to);
                }
            }
        }
    }

    for (size_t loops = 0; loops < 50; loops++) {
        for (char i = 'A'; i <= 'Z'; i++) {
            if (terminal[i]) continue;
            for (const auto &unf : unfolding[i]) {
                bool all = true;
                for (char k : unf) all &= terminal[k];
                if (all) terminal[i] = true;
            }
        }
    }

    if (terminal[start]) {
        ans[start] = true;
        q.push(start);
    }

    while (!q.empty()) {
        char v = q.front();
        q.pop();
        for (auto &i : unfolding[v]) {
            bool all = true;
            for (char &j : i) all &= terminal[j];
            if (!all) continue;

            for (char &j : i) {
                if (!ans[j]) {
                    ans[j] = true;
                    q.push(j);
                }
            }
        }
    }

    for (char i = 'A'; i <= 'Z'; i++)
        if (present.find(i) != present.end() &&
            !(visited[i] && terminal[i] && ans[i]))
            cout << i << " ";
    return 0;
}