#include <bits/stdc++.h>

using namespace std;
const int MOD = 999999937;

bool debug = false;

vector<vector<long long>> trans = {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 0 },
};

vector<vector<long long>> tmp = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

vector<vector<long long>> ml = {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 0, 1, 0 },
    { 1, 1, 0, 1, 0 },
};

vector<vector<long long>> result;

void matrixPrint(vector<vector<long long>> a) {
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            cout << a[i][j] << ' ';
        }
        cout <<endl;
    }
    cout <<endl;
}

void matrixMul(vector<vector<long long>> &a, vector<vector<long long>> &b) {
    if (debug) {
        cout << "multiplying:\n";
        matrixPrint(a);
        matrixPrint(b);
    }
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            tmp[i][j] = 0;
            for (size_t v = 0; v < 5; v++) {
                tmp[i][j] = (tmp[i][j] + a[i][v] * b[v][j]) % MOD;
            }
        }
    }
    if (debug) {
        cout << "result:\n";
        matrixPrint(tmp);
    }
}

void binMul(long long pw) {
    while (pw) {
        if (debug) {
            cout << pw << endl;
        }
        if (pw & 1) {
            matrixMul(result, trans);
            result = tmp;
        }
        matrixMul(trans, trans);
        trans = tmp;
        pw /= 2;
    }
}

long long getAns() {
    long long retv = 0;
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            retv = (retv + result[i][j]) % MOD;
        }
    }
    return retv;
}

int main() {
    long long n;
    while (cin >> n) {
        trans = ml;
        result = trans;
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            cout << 5 << endl;
        } else {
            binMul(n - 2);
            cout << getAns() << endl;
        }
    }
    return 0;
}
