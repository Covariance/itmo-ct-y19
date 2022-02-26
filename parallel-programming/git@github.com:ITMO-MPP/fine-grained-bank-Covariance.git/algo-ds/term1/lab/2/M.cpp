#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
vector<bool> seq;
vector< vector< pair<int, int> > > web;
vector< pair<int, int > > em;

bool nextSeq() {
    uint i = 0;
    while (i < seq.size() && seq[i]) {
        seq[i] = false;
        i++;
    }
    if (i < seq.size()) {
        seq[i] = true;
        return true;
    }
    return false;
}

bool check() {
    vector<bool> seqCopy = seq;
    for (uint i = 0; i < web.size(); i++) {
        for (uint j = 0; j < web[i].size(); j ++) {
            if (seqCopy[web[i][j].first] && !seqCopy[web[i][j].second]) {
                seqCopy[web[i][j].first] = false;
                seqCopy[web[i][j].second] = true;
            }
        }
    }
    for (uint i = 0; i < seqCopy.size() - 1; i++) {
        if (seqCopy[i] > seqCopy[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, k, a, b;
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        seq.push_back(false);
    }
    for (int i = 0; i < k; i++) {
        web.push_back(em);
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> a >> b;
            web[i].push_back(make_pair(min(a - 1, b - 1), max(a - 1, b - 1)));
        }
    }
    while (nextSeq()) {
        if (!check()) {
            cout <<"No" <<endl;
            return 0;
        }
    }
    cout <<"Yes" <<endl;
    return 0;
}
