#include <bits/stdc++.h>

using namespace std;
pair<int, int> a[10][8];

void web16() {
    /// done 0
    a[0][0] = make_pair(1, 2);
    a[0][1] = make_pair(3, 4);
    a[0][2] = make_pair(5, 6);
    a[0][3] = make_pair(7, 8);
    a[0][4] = make_pair(9, 10);
    a[0][5] = make_pair(11, 12);
    a[0][6] = make_pair(13, 14);
    a[0][7] = make_pair(15, 16);

    /// done 1

    a[1][0] = make_pair(1, 4);
    a[1][1] = make_pair(2, 3);
    a[1][2] = make_pair(5, 8);
    a[1][3] = make_pair(6, 7);
    a[1][4] = make_pair(9, 12);
    a[1][5] = make_pair(10, 11);
    a[1][6] = make_pair(13, 16);
    a[1][7] = make_pair(14, 15);

    /// done 2
    a[2][0] = make_pair(1, 2);
    a[2][1] = make_pair(3, 4);
    a[2][2] = make_pair(5, 6);
    a[2][3] = make_pair(7, 8);
    a[2][4] = make_pair(9, 10);
    a[2][5] = make_pair(11, 12);
    a[2][6] = make_pair(13, 14);
    a[2][7] = make_pair(15, 16);

    /// done 3
    a[3][0] = make_pair(1, 8);
    a[3][1] = make_pair(2, 7);
    a[3][2] = make_pair(3, 6);
    a[3][3] = make_pair(4, 5);
    a[3][4] = make_pair(9, 16);
    a[3][5] = make_pair(10, 15);
    a[3][6] = make_pair(11, 14);
    a[3][7] = make_pair(12, 13);

    /// done 4
    a[4][0] = make_pair(1, 3);
    a[4][1] = make_pair(2, 4);
    a[4][2] = make_pair(5, 7);
    a[4][3] = make_pair(6, 8);
    a[4][4] = make_pair(9, 11);
    a[4][5] = make_pair(10, 12);
    a[4][6] = make_pair(13, 15);
    a[4][7] = make_pair(14, 16);

    /// done 5
    a[5][0] = make_pair(1, 2);
    a[5][1] = make_pair(3, 4);
    a[5][2] = make_pair(5, 6);
    a[5][3] = make_pair(7, 8);
    a[5][4] = make_pair(9, 10);
    a[5][5] = make_pair(11, 12);
    a[5][6] = make_pair(13, 14);
    a[5][7] = make_pair(15, 16);

    /// done 6
    a[6][0] = make_pair(1, 16);
    a[6][1] = make_pair(2, 15);
    a[6][2] = make_pair(3, 14);
    a[6][3] = make_pair(4, 13);
    a[6][4] = make_pair(5, 12);
    a[6][5] = make_pair(6, 11);
    a[6][6] = make_pair(7, 10);
    a[6][7] = make_pair(8, 9);

    /// done 7
    a[7][0] = make_pair(1, 5);
    a[7][1] = make_pair(2, 6);
    a[7][2] = make_pair(3, 7);
    a[7][3] = make_pair(4, 8);
    a[7][4] = make_pair(9, 13);
    a[7][5] = make_pair(10, 14);
    a[7][6] = make_pair(11, 15);
    a[7][7] = make_pair(12, 16);

    /// done 8
    a[8][0] = make_pair(1, 3);
    a[8][1] = make_pair(2, 4);
    a[8][2] = make_pair(5, 7);
    a[8][3] = make_pair(6, 8);
    a[8][4] = make_pair(9, 11);
    a[8][5] = make_pair(10, 12);
    a[8][6] = make_pair(13, 15);
    a[8][7] = make_pair(14, 16);

    /// done 9
    a[9][0] = make_pair(1, 2);
    a[9][1] = make_pair(3, 4);
    a[9][2] = make_pair(5, 6);
    a[9][3] = make_pair(7, 8);
    a[9][4] = make_pair(9, 10);
    a[9][5] = make_pair(11, 12);
    a[9][6] = make_pair(13, 14);
    a[9][7] = make_pair(15, 16);
}

int main() {
    web16();
    int n;
    cin >> n;

    int sum = 0;
    int layerSum[10];
    int layers = 0;

    for (int i = 0; i < 10; i++) {
        layerSum[i] = 0;
        for (int j = 0; j < 8; j++) {
            if (a[i][j].first <= n && a[i][j].second <= n) {
                layerSum[i]++;
                sum++;
            }
        }
        if (layerSum[i] != 0) {
            layers++;
        }
    }
    cout <<n <<' ' <<sum <<' ' <<layers <<endl;
    for (int i = 0; i < 10; i++) {
        if (layerSum[i] != 0) {
            cout <<layerSum[i] <<' ';
            for (int j = 0; j < 8; j++) {
                if (a[i][j].first <= n && a[i][j].second <= n) {
                    cout <<a[i][j].first <<' ' <<a[i][j].second <<' ';
                }
            }
            cout <<endl;
        }
    }
    return 0;
}
