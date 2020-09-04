#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

vector< pair< pair<ll, ll>, int > > gems;
vector< pair< pair<ll, ll>, int > > tmp;

int n, k;
ld t;

vector<int> ans;
vector<int> anstmp;

void read() {
    cin >> n >> k;
    gems.resize(n);
    tmp.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> gems[i].fs.fs >> gems[i].fs.sc;
        gems[i].sc = i;
    }
}

bool leq(int i, int j) {
    return ((ld)gems[i].fs.fs - t * gems[i].fs.sc <= (ld)gems[j].fs.fs - t * gems[j].fs.sc);
}

void mergesort(int l, int r) {
    if (l + 1 < r) {
        mergesort(l, (l + r) / 2);
        mergesort((l + r) / 2, r);
        int lp = l, rp = (l + r) / 2;
        for (int i = l; i < r; i++) {
            if (lp < (l + r) / 2) {
                if (rp < r) {
                    if (leq(lp, rp)) {
                        tmp[i] = gems[lp];
                        lp++;
                    } else {
                        tmp[i] = gems[rp];
                        rp++;
                    }
                } else {
                    tmp[i] = gems[lp];
                    lp++;
                }
            } else {
                tmp[i] = gems[rp];
                rp++;
            }
        }
        for (int i = l; i < r; i++) {
            gems[i] = tmp[i];
        }
    }
}

void mergesort2(int l, int r) {
    if (l + 1 < r) {
        mergesort2(l, (l + r) / 2);
        mergesort2((l + r) / 2, r);
        int lp = l, rp = (l + r) / 2;
        for (int i = l; i < r; i++) {
            if (lp < (l + r) / 2) {
                if (rp < r) {
                    if (ans[lp] <= ans[rp]) {
                        anstmp[i] = ans[lp];
                        lp++;
                    } else {
                        anstmp[i] = ans[rp];
                        rp++;
                    }
                } else {
                    anstmp[i] = ans[lp];
                    lp++;
                }
            } else {
                anstmp[i] = ans[rp];
                rp++;
            }
        }
        for (int i = l; i < r; i++) {
            ans[i] = anstmp[i];
        }
    }
}

bool check(bool print) {
    mergesort(0, n);
    ld sum = 0;
    for (int i = 0; i < k; i++) {
        sum += (ld)gems[n - i - 1].fs.fs - t * gems[n - i - 1].fs.sc;
        if (print) {
            ans.push_back(gems[n - i - 1].sc + 1);
        }
    }

    if (print) {
        anstmp.resize(ans.size());
        mergesort2(0, k);
        for (int i = 0; i < k; i++) {
            cout << ans[i] << ' ';
        }
    }
    return (sum >= 0);
}


int main() {
    read();
    ld l = 0.0, r = 1e7;
    while (r - l > 1e-7) {
        t = l + (r - l) / 2;
        if (check(false)) {
            l = t;
        } else {
            r = t;
        }
    }
    t = l;
    if (check(false)) {
        check(true);
    } else {
        t = r;
        check(true);
    }
    return 0;
}
