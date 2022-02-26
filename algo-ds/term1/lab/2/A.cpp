#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int partition(vector<ll>* arr, int l, int r) {
    ll x = (*arr)[l + (rand() % (r - l))];
    int i = l, j = r;
    while (i <= j) {
        while ((*arr)[i] < x) {
            i++;
        }
        while ((*arr)[j] > x) {
            j--;
        }
        if (i <= j) {
            std::swap((*arr)[i], (*arr)[j]);
            i++;
            j--;
        }
    }
    if (i - 2 == j) {
        j++;
    }
    return j;
}

void quickcsort(vector<ll>* arr, int l, int r) {
    if (l < r) {
        int x = partition(arr, l, r);
        quickcsort(arr, l, x);
        quickcsort(arr, x + 1, r);
    }
}

int main() {
    int n;
    cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(0);
        cin >> arr[i];
    }
    quickcsort(&arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    return 0;
}
