#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;
const int INF = 100000;
bool debug = false;

int main() {
    if (!debug) {
        freopen("number.in", "r", stdin);
        freopen("number.out", "w", stdout);
    }
    int n;
    cin >> n;
    vector<vector<char>> symbol(n, vector<char>(n + 1, 0));
    vector<vector<int>> len(n, vector<int>(n + 1, INF));
    vector<vector<pair<int, int>>> lastCell(n, vector<pair<int, int>>(n + 1, make_pair(-1, -1)));
    queue<pair<int, int>> order;
    lastCell[0][0] = make_pair(0, 0);
    len[0][0] = 0;
    order.push(make_pair(0, 0));
    pair<int, int> curCell;
    while (order.size() > 0) {
        curCell = order.front();
        order.pop();
        for (int i = 0; i < min(n - curCell.sc + 1, 10); i++) {
            pair<int, int> newCell = make_pair(((10 * curCell.fs + i) % n), curCell.sc + i);
            if (len[newCell.fs][newCell.sc] == INF) {
                lastCell[newCell.fs][newCell.sc] = curCell;
                symbol[newCell.fs][newCell.sc] = (char) ('0' + i);
                len[newCell.fs][newCell.sc] = len[curCell.fs][curCell.sc] + 1;
                order.push(newCell);
            }
        }
    }
    curCell = make_pair(0, n);
    vector<char> res;
    while (curCell != lastCell[curCell.fs][curCell.sc]) {
        res.push_back(symbol[curCell.fs][curCell.sc]);
        curCell = lastCell[curCell.fs][curCell.sc];
    }
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[res.size() - i - 1];
    }
    return 0;
}
