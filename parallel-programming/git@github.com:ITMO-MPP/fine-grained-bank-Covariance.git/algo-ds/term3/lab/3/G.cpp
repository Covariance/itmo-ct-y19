//
// Created by covariance on 13.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, lst;

int main() {
    int n, tmp;
    cin >> n;

    g.resize(n);
    lst.assign(n, vector<int>());

    int pow_check = 0;
    for (int i = 0; i != n; ++i) {
        g[i].assign(n, 0);
        int cnt;
        cin >> cnt;
        pow_check += cnt % 2;
        for (int j = 0; j != cnt; ++j) {
            cin >> tmp;
            ++g[i][tmp - 1];
            lst[i].push_back(tmp - 1);
        }
    }

    if (pow_check != 0 && pow_check != 2) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> st, ans;
    st.push_back(0);
    while (!st.empty()) {
        int cur = st.back();
        while (!(lst[cur].empty() || g[cur][tmp = lst[cur].back()])) {
            lst[cur].pop_back();
        }

        if (lst[cur].empty()) {
            ans.push_back(cur + 1);
            st.pop_back();
        } else {
            st.push_back(tmp);
            --g[cur][tmp];
            --g[tmp][cur];
        }
    }
    cout << ans.size() - 1 << endl;
    for (int v : ans) {
        cout << v << ' ';
    }
    return 0;
}
