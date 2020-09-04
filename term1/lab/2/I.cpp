#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef unsigned int uint;
typedef long long ll;
vector< pair<ll, ll> > shop;
int p;
int m, n;

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

void read() {
    cin >> m;
    shop.resize(m);
    ll a, b, t;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> t;
        shop[i].first = b + t;
        shop[i].second = a;
    }
    cin >> n >> p;
}

bool check(ll t) {
    vector<ll> arr;
    arr.resize(m);
    for (int i = 0; i < m; i++) {
        if (shop[i].second == 0) {
            arr[i] = (t - shop[i].first >= 0L) ? p : 0;
        } else {
            arr[i] = (t - shop[i].first >= 0L) ? ((t - shop[i].first)/shop[i].second) : 0;
        }
    }
    ll sum = 0;
    quickcsort(&arr, 0, m);
    for (int i = 0; i < min(n, m); i++) {
        sum += arr[m - i - 1];
    }
    return (sum >= p);
}

bool checkCountSort(ll time) {
	vector<ll> arr;
	for (int i = 0; i < p + 1; i++) {
        arr.push_back(0L);
	}

	ll curSt = 0, sum = 0, t;

	for (int i = 0; i < m; i++) {
		if (time >= shop[i].first) {
			if (shop[i].second == 0) {
				arr[p]++;
			} else {
				t = (time - shop[i].first) / shop[i].second;
				if (t > p) {
                    t = p;
				}
				arr[(int)t]++;
			}
		}
	}

	for (int i = p; i > 0 && curSt < n; i--) {
		t = arr[i];
		if (n - curSt < t) t = n - curSt;
		sum += t*i;
		curSt += t;
	}
	return (sum >= p);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    read();
    ll l = 0, mid, r = 2e10 + 1;
    while (l < r) {
		mid = l + (r - l) / 2;
		if (checkCountSort(mid)) {
            r = mid;
		} else {
            l = mid + 1;
		}
	}
	cout << l;
    return 0;
}
