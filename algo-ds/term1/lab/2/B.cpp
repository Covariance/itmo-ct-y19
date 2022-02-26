#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cin >> m;
    int l, mid, r;
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;

        l = -1; r = n - 1;
        while (l + 1 < r) {
            mid = (l + r)/2;
            if (arr[mid] < x) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if (arr[r] != x) {
            std::cout <<"-1 -1\n";
            continue;
        }
        std::cout << r + 1 <<' ';

        l = 0, r = n;
        while (l + 1 < r) {
            mid = (l + r)/2;
            if (arr[mid] > x) {
                r = mid;
            } else {
                l = mid;
            }
        }
        std::cout << l + 1 <<std::endl;
    }
    return 0;
}
