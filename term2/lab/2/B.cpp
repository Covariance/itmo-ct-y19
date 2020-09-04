//
// Created by covariance on 14.03.2020.
//
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#include <utility>

using namespace std;

unsigned int hsh(int x) {
    return abs(x % 31627 + x / 31627);
}

unsigned int hsh(const string& x) {
    unsigned int res = 0;
    for (size_t i = 0; i < x.size(); i++) {
        res *= 37;
        res += x[i] + 7 * (i & 1);
    }
    return res % 70000;
}

typedef struct element {
    string key, val;
    bool del;

    element(string key, string val) {
        this->key = std::move(key);
        this->val = std::move(val);
        this->del = false;
    }
} el;

vector<element> table[70000];

int main() {
    ifstream in("map.in");
    ofstream out("map.out");

    in.tie(nullptr);
    out.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string command;
    string key, val;
    bool flag = false;
    while (in >> command >> key) {
        unsigned int x = hsh(key);
        flag = false;
        switch (command[0]) {
            case 'p':
                in >> val;
                for (auto &i : table[x]) {
                    if (i.key == key) {
                        i.val = val;
                        i.del = false;
                        flag = true;
                        break;
                    }
                }
                if (!flag) table[x].emplace_back(key, val);
                break;
            case 'g':
                for (const auto& a : table[x]) {
                    if (a.key == key) {
                        flag = true;
                        if (!a.del) {
                            out << a.val << "\n";
                        } else {
                            out << "none\n";
                        }
                        break;
                    }
                }
                if (!flag) out << "none\n";
                break;
            default:
                for (auto &i : table[x]) {
                    if (i.key == key) {
                        i.del = true;
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
