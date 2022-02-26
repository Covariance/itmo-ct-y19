//
// Created by covariance on 25.05.2020.
//
#include <bits/stdc++.h>

#define fs first
#define sc second

using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

uint counts[1000001];
vector<uint> arr;
vector<pair<pair<size_t, size_t>, size_t>> queries;
vector<ull> ans;

ull cur_ans = 0;
int cur_l = -1, cur_r = -1;

ull get_ans(int left, int right) {
    while (cur_r < right) {
        cur_r++;
        cur_ans += arr[cur_r] * ((counts[arr[cur_r]] << 1) + 1);
        counts[arr[cur_r]]++;
    }
    while (cur_l > left) {
        cur_l--;
        cur_ans += arr[cur_l] * ((counts[arr[cur_l]] << 1) + 1);
        counts[arr[cur_l]]++;
    }
    while (cur_r > right) {
        counts[arr[cur_r]]--;
        cur_ans -= arr[cur_r] * ((counts[arr[cur_r]] << 1) + 1);
        cur_r--;
    }
    while (cur_l < left) {
        if (cur_l != -1) {
            counts[arr[cur_l]]--;
            cur_ans -= arr[cur_l] * ((counts[arr[cur_l]] << 1) + 1);
        }
        cur_l++;
    }
    return cur_ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    size_t n, m;
    int block_size;
    cin >> n >> m;
    arr.resize(n);
    ans.resize(m);
    queries.resize(m);
    block_size = 800;

    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
        counts[arr[i]] = 0;
    }

    size_t a, b;
    for (size_t i = 0; i < m; i++) {
        cin >> a >> b;
        queries[i] = {{a - 1, b - 1}, i};
    }

    sort(queries.begin(), queries.end(),
         [block_size](auto a, auto b) {
             if (a.fs.fs / block_size != b.fs.fs / block_size) {
                 return a.fs.fs < b.fs.fs;
             }
             return a.fs.sc < b.fs.sc;
         });
    for (auto query : queries) {
        ans[query.sc] = get_ans((int) query.fs.fs, (int) query.fs.sc);
    }

    for (auto result : ans) {
        cout << result << "\n";
    }

    return 0;
}
