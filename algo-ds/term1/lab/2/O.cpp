#include <bits/stdc++.h>

using namespace std;
vector< pair<int, int> > a;
typedef unsigned int uint;

int bubbleSortExcept(vector<int> excl, string* res) {
    int retv = 0;
    for (int i = 1; i <= 10; i++) {
        bool add1 = true;
        for (uint k = 0; k < excl.size(); k++) {
            if (i == excl[k]) {
                add1 = false;
            }
        }
        if (add1) {
            for (int j = i + 1; j <= 10; j++) {
                bool add2 = true;
                for (uint k = 0; k < excl.size(); k++) {
                    if (j == excl[k]) {
                        add2 = false;
                    }
                }
                if (add2) {
                    (*res).append(to_string(i))
                        .append(" ")
                        .append(to_string(j))
                        .append("\n");
                    retv++;
                }
            }
        }
    }
    return retv;
}

bool solve(int n) {
    int *seq = new int[n];
    bool isSorted = true;
    int firstOne = 0, lastZero = n - 1;
    vector<int> base;
    vector<int> ones;
    vector<int> zeros;
    vector<int> prefix;
    vector<int> suffix;
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
        if (i > 0 && seq[i] < seq[i - 1]) {
            isSorted = false;
        }
        if (seq[i] == 1) {
            ones.push_back(i + 1);
        } else {
            zeros.push_back(i + 1);
        }
    }
    if (isSorted) {
        cout << -1 << endl;
        return false;
    }
    while (seq[firstOne] != 1) {
        firstOne++;
    }
    while (seq[lastZero] != 0) {
        lastZero--;
    }
    for (uint i = 0; i < zeros.size(); i++) {
        prefix.push_back(i + 1);
    }
    for (uint i = 0; i < ones.size(); i++) {
        suffix.push_back(n - i);
    }
    for (int i = n + 1; i <= 16; i++) {
        base.push_back(i);
        ones.push_back(i);
        zeros.push_back(i);
        prefix.push_back(i);
        suffix.push_back(i);
    }
    base.push_back(firstOne + 1);
    base.push_back(lastZero + 1);
    string out = "";
    int sum = 0;
    sum += bubbleSortExcept(ones, &out);
    sum += bubbleSortExcept(zeros, &out);
    sum += bubbleSortExcept(base, &out);
    sum += bubbleSortExcept(prefix, &out);
    sum += bubbleSortExcept(suffix, &out);
    cout << sum << endl << out;
    return true;
}

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        solve(n);
        cin >> n;
    }
    return 0;
}
