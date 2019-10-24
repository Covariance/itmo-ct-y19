#include <bits/stdc++.h>

using namespace std;

vector<int> values;

bool checkDisjunction(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1 && values[i] != 0) {
            return true;
        }
        if (arr[i] == 0 && values[i] != 1) {
            return true;
        }
    }
    return false;
}

void updateDisjunction(vector<int>* arr) {
    for (int i = 0; i < (*arr).size(); i++) {
        if ((*arr)[i] == 1 && values[i] == 1) {
            (*arr)[i] = -1;
        }
        if ((*arr)[i] == 0 && values[i] == 0) {
            (*arr)[i] = -1;
        }
    }
}

bool isLoneDisjunction(vector<int> arr) {
    bool metOne = false;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != -1) {
            if (metOne) {
                return false;
            } else {
                metOne = true;
            }
        }
    }
    return metOne;
}

void solveLoneDisjunction(vector<int>* arr, int* changes) {
    for (int i = 0; i < (*arr).size(); i++) {
        if ((*arr)[i] != -1) {
            values[i] = (*arr)[i];
            changes++;
        }
    }
}

int main() {
    int n, k, a;
    cin >> n >> k;

    if (k == 0) {
        cout <<"YES";
        return 0;
    }

    vector< vector<int> > form;
    for (int i = 0; i < n; i++) {
        values.push_back(-1);
    }
    for (int i = 0; i < k; i++) {
        form.push_back(*(new vector<int>));
        for (int j = 0; j < n; j++) {
            cin >> a;
            form[i].push_back(a);
        }
    }

    int changes = 1;
    while (changes != 0) {
        changes = 0;
        int i = 0;
        while (i < k && !isLoneDisjunction(form[i])) {
            i++;
        }
        if (i == k) {
            cout << "NO";
            return 0;
        }
        solveLoneDisjunction(&form[i], &changes);
        i = 0;
        while (i < k && checkDisjunction(form[i])) {
            updateDisjunction(&form[i]);
            i++;
        }
        if (i != k) {
            cout << "YES";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}
