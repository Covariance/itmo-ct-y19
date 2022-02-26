#include <bits/stdc++.h>

using namespace std;

bool debug = false;

int main() {
    int n;
    cin >> n;
    int *arr = new int[n + 1];
    for (int i = 1; i < n + 1; i++) {
        cin >> arr[i];
    }
    for (int i = 2; i < n + 1; i++) {
        if (arr[i] < arr[i/2]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
