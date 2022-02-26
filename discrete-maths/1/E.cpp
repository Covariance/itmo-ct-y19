#include <bits/stdc++.h>

using namespace std;

int n, k = 0;
vector< vector<int> > f;
vector< vector<int> > matrix;
vector<bool> matrixDone;
vector< vector<int> > table;

void buildLeafMatrix(int index, int v) {
    int cnt = 0;
    for (int i = 0; i < (1 << v); i++) {
        for (int j = 0; j < (1 << (k - v - 1)); j++) {
            matrix[index][cnt] = 0;
            cnt++;
        }
        for (int j = 0; j < (1 << (k - v - 1)); j++) {
            matrix[index][cnt] = 1;
            cnt++;
        }
    }
}

void buildMatrix(int v) {
    if (!matrixDone[v]) {
        matrixDone[v] = true;
        for (int i = 0; i < (1 << k); i++) {
            int row = 0;
            int ln = f[v].size();
            for (int j = 0; j < ln; j++) {
                row += (1 << (ln - j - 1)) * matrix[f[v][j]][i];
            }
            matrix[v][i] = table[v][row];
        }
    }
}

int dfs(int v) {
    int retv = 0;
    for (size_t i = 0; i < f[v].size(); i++) {
        retv = max(dfs(f[v][i]), retv);
    }
    buildMatrix(v);
    return retv + 1;
}

void initialize() {
    f.resize(n);
    matrix.resize(n);
    matrixDone.resize(n);
    table.resize(n);
    for (int i = 0; i < n; i++) matrixDone[i] = false;
}

int main() {
    cin >> n;
    initialize();
    for (int i = 0; i < n; i++) {
        int w; cin >> w;
        if (w == 0) {
            matrixDone[i] = true;
            k++;
        } else {
            f[i].resize(w);
            table[i].resize((1 << w));
            for (int j = 0; j < w; j++) {
                cin >> f[i][j];
                f[i][j]--;
            }
            for (int j = 0; j < (1 << w); j++) {
                cin >> table[i][j];
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        matrix[i].resize((1 << k));
        if (matrixDone[i]) {
            buildLeafMatrix(i, cnt);
            cnt++;
        }
    }

    cout << dfs(n - 1) - 1 << endl;
    for (int i = 0; i < (1 << k); i++) {
        cout <<matrix[matrix.size() - 1][i];
    }
    return 0;
}
