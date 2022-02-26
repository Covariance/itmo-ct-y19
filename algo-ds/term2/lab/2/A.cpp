//
// Created by covariance on 14.03.2020.
//
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

unsigned int myHash(int x) {
    return abs(x % 31627 + x / 31627);
}

vector<pair<int, bool>> table[70000];

int main() {
    ifstream in("set.in");
    ofstream out("set.out");

    in.tie(nullptr);
    out.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string command;
    int num;
    unsigned int x;
    bool flag = false;
    while (in >> command >> num) {
        x = myHash(num);
        flag = false;
        switch (command[0]) {
            case 'i':
                for (auto &i : table[x]) {
                    if (i.first == num) {
                        i.second = true;
                        flag = true;
                        break;
                    }
                }
                if (!flag) table[x].emplace_back(num, true);
                break;
            case 'e':
                for (auto a : table[x]) {
                    if (a.first == num) {
                        flag = true;
                        if (a.second) {
                            out << "true\n";
                        } else {
                            out << "false\n";
                        }
                        break;
                    }
                }
                if (!flag) out << "false\n";
                break;
            default:
                for (auto &i : table[x]) {
                    if (i.first == num) {
                        i.second = false;
                        break;
                    }
                }
                break;
        }
    }

    in.close();
    out.close();
    return 0;
}
