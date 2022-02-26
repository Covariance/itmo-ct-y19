#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >>n >>k;
    int arr[n];
    for (int i = 0; i < n; i++) cin >>arr[i];
    pair<int, int> candidates[k-1];
    for (int j = 0; j < k - 1; j++) candidates[j] = make_pair(0, 0);
    for (int i = 0; i < n; i++) {
        bool found_identical = false;
        for (int j = 0; j < k - 1; j++) {
            if (candidates[j].first == arr[i]) {
                found_identical = true;
                candidates[j].second++;
                break;
            }
        }
        bool found_zero = false;
        if (!found_identical) {
            for (int j = 0; j < k - 1; j++) {
                if (candidates[j].second == 0) {
                    found_zero = true;
                    candidates[j].first = arr[i];
                    candidates[j].second = 1;
                    break;
                }
            }
        }
        if (!found_identical && !found_zero) {
            for (int j = 0; j < k - 1; j++) {
                candidates[j].second--;
            }
        }
    }
    for (int j = 0; j < k - 1; j++) {
        if (candidates[j].second > 0) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (candidates[j].first == arr[i]) {
                    cnt++;
                }
            }
            if (cnt > n/k) {
                cout <<candidates[j].first <<' ';
            }
        }
    }
    return 0;
}
