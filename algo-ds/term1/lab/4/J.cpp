#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = true;

void findLCS(int m, int n, string str1, string str2, int retv[]) {
	vector<vector<int>> k(2, vector<int>(n + 1, 0));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j <= n; j++) {
            k[0][j] = k[1][j];
		}

		for (int j = 1; j <= n; j++) {
            k[1][j] = (str1[i] == str2[j -1]) ? k[0][j-1] + 1 :
                 max(k[1][j-1], k[0][j]);
		}
	}
	for (int i = 0; i <= n; i++) {
        retv[i] = k[1][i];
	}
}

string hirsh(string str1, string str2) {
    int m = str1.length(), n = str2.length();
	if(n == 0) {
	    return "";
	}
    if (m == 1) {
        if (str2.find(str1[0]) != string::npos) {
            return str1;
        }
        return "";
    }

	string str1_rev = str1, str2_rev = str2;
	reverse(str1_rev.begin(), str1_rev.end());
	reverse(str2_rev.begin(), str2_rev.end());

	int *first = new int[n + 1], *second = new int[n + 1];
    int div = m / 2;
	findLCS(div, n, str1.substr(0, div), str2, first);
    findLCS(div + 1, n, str1_rev.substr(0, m - div), str2_rev, second);

	int mx = 0, k = 0;
	for (int i = 0; i <= n; i++) {
        mx = (first[i] + second[n - i] > mx) ? first[(k = i)] + second[n - i] : mx;
	}
	div = (div == 0) ? 1 : div;
	return hirsh(str1.substr(0, div), str2.substr(0, k ))
            .append(hirsh(str1.substr(div, m), str2.substr(k, n)));
}

int main() {
    string s, t;
    cin >> s >> t;
    cout << hirsh(s, t);
	return 0;
}
