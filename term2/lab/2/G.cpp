//
// Created by covariance on 22.03.2020.
//
#include <bits/stdc++.h>

typedef unsigned int uint;
typedef unsigned long long ull;
using namespace std;

struct node {
    vector<uint> e;
    uint size;
    bool f;
};

vector<node> g;
pair<int, int> rt;
vector<uint> dist;
ull BIG_MOD = 19741194522LL;

uint getSize(uint x, uint par) {
    if (!g[x].f) {
        uint res = 0;
        for (uint i = 0; i < g[x].e.size(); i++) {
            if (g[x].e[i] != par) {
                res += getSize(g[x].e[i], x);
            }
        }
        g[x].f = true;
        g[x].size = res + 1;
    }
    return g[x].size;
}

ull hsh1(uint x, uint par) {
    ull res = 0;
    for (uint i = 0; i < g[x].e.size(); i++) {
        if (g[x].e[i] != par) {
            ull h = hsh1(g[x].e[i], x);
            res +=  419420322 * h * h * getSize(g[x].e[i], x) + 1488;
        }
    }
    return res % BIG_MOD;
}

ull hsh2(uint x, uint par) {
    ull res = 0;
    for (uint i = 0; i < g[x].e.size(); i++) {
        if (g[x].e[i] != par) {
            ull s = getSize(g[x].e[i], x);
            ull h = hsh1(g[x].e[i], x);
            res += 15 * h * s + 1;
        }
    }
    return res;
}

void distSearchDFS(uint v, uint p, uint curDist) {
    dist[v] = curDist;
    for (uint a : g[v].e) {
        if (a != p) {
            distSearchDFS(a, v, curDist + 1);
        }
    }
}

bool midSearchDFS(uint v, uint p, uint dst, uint fin) {
    if (v == fin) {
        return true;
    }
    bool flag = false;
    for (uint a : g[v].e) {
        if (a != p) {
            flag |= midSearchDFS(a, v, dst, fin);
        }
    }
    if (flag) {
        if (dist[v] == dst / 2) {
            rt.first = v;
        }
        if (dist[v] == (dst + 1) / 2) {
            rt.second = v;
        }
    }
    return flag;
}

void clear() {
    for (auto &i : g) {
        i.f = false;
    }
}

bool check(vector<ull> nums) {
    if (nums.size() % 2 != 0) {
        return false;
    }
    sort(nums.begin(), nums.end());
    ull last = nums[0];
    uint cnt = 1;
    for (size_t i = 1; i < nums.size(); i++) {
        while (i < nums.size() && nums[i++] == last) {
            cnt++;
        }
        if (cnt % 2 != 0) {
            return false;
        }
        cnt = 0;
        if (i < nums.size()) {
            last = nums[i];
        }
    }
    return true;
}

bool check(uint v) {
    clear();
    vector<ull> nums1;
    vector<ull> nums2;
    for (uint i = 0; i < g[v].e.size(); i++) {
        ull x = hsh1(g[v].e[i], v);
        nums1.push_back(x);
        x = hsh2(g[v].e[i], v);
        nums2.push_back(x);
    }
    return check(nums1) || check(nums2);
}

int main() {
    uint n;
    cin >> n;
    if (n == 1) {
        cout << "NO";
        return 0;
    }
    g.resize(n);
    uint u, v;
    for (size_t i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        g[u].e.push_back(v);
        g[v].e.push_back(u);
    }

    dist.resize(n, 0);
    distSearchDFS(0, 0, 0);

    int maxDist = 0;
    for (size_t i = 0; i < n; i++) {
        if (dist[i] > dist[maxDist]) {
            maxDist = i;
        }
    }

    dist.resize(n, 0);
    distSearchDFS(maxDist, maxDist, 0);

    int maxDist2 = maxDist;
    for (size_t i = 0; i < n; i++) {
        if (dist[i] > dist[maxDist2]) {
            maxDist2 = i;
        }
    }

    midSearchDFS(maxDist, maxDist, dist[maxDist2], maxDist2);

    if (rt.first != rt.second) {
        cout << "NO";
        return 0;
    }

    if (check(rt.first) || check(rt.second)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
