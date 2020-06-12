//
// Created by covariance on 05.06.2020.
//
#include <bits/stdc++.h>

#define TERMINAL 0
#define UNKNOWN 1
#define ABSENT 2

using namespace std;

unordered_map<char, vector<unordered_set<char>>> g;
unordered_map<char, int> color;

bool terminal_unfolding(const unordered_set<char> &unfolding) {
    for (char term : unfolding)
        if (('a' <= term && term <= 'z') || (color[term] != TERMINAL))
            return false;
    return true;
}

int main() {
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    for (char i = 'A'; i <= 'Z'; i++) {
        color[i] = UNKNOWN;
        g[i] = vector<unordered_set<char>>(0);
    }


    int n;
    char start;
    cin >> n >> start;
    string s;
    getline(cin, s);
    for (int i = 0; i < n; i++) {
        getline(cin, s);
        char from = s[0];
        bool valuable = true;
        unordered_set<char> unfolding;
        for (int j = 5; j < s.length() && s[j] != '\n'; j++)
            unfolding.insert(s[j]);
        if (color[from] != TERMINAL) {
            color[from] = unfolding.empty() ? TERMINAL : UNKNOWN;
            if (!unfolding.empty()) g[from].push_back(unfolding);
        }
    }
    for (int rounds = 0; rounds <= 100; rounds++) {
        for (char i = 'A'; i <= 'Z'; i++) {
            if (color[i] == TERMINAL) continue;
            for (const auto &unfolding : g[i])
                if (terminal_unfolding(unfolding))
                    color[i] = TERMINAL;
        }
    }

    for (char i = 'A'; i <= 'Z'; i++)
        if (color[i] == TERMINAL) cout << i << ' ';

    return 0;
}
