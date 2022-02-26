#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

vector< pair <int, int> > arr;
int n, k;

void read() {
    int A, B, C, a1, a2;
    arr.resize(n);
    cin >> A >> B >> C >> a1 >> a2;
    int cnt = 2;
    arr[0].fs = a1;
    arr[1].fs = a2;
    while (cnt < n) {
        arr[cnt].fs = (A*arr[cnt - 2].fs + B*arr[cnt - 1].fs + C);
        cnt++;
    }
}

int partition(vector< pair<int, int> > &arr, int l, int r) {
    if (l == r) {
        return l;
    }
    int i = l, j = r;
    while (true) {
        while (arr[i].fs < arr[r].fs) {
            i++;
        }
        while (arr[j].fs > arr[r].fs) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(arr[i++], arr[j--]);
    }
    swap(arr[i], arr[r]);
    return i;
}

int kOrder(vector< pair<int, int> > &arr) {
    int kTmp = k - 1;
    int l = 0, r = n - 1;
    while (true) {
        int div = partition(arr, l, r);
        if (kTmp == div) {
            return (arr[div].fs);
        }
        if (kTmp < div) {
            r = div - 1;
        } else {
            l = div + 1;
        }
    }
}

int main() {
    cin >> n >> k;
    read();
    cout <<kOrder(arr);
    return 0;
}
