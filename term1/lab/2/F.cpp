#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(i + 1);
    }
    for (int i = 2; i < n; i++) {
        swap(a[i], a[i/2]);
    }
    for (int i = 0; i < n; i++) {
        cout <<a[i] <<' ';
    }
    return 0;
}
