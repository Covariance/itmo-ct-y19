//
// Created by covariance on 14.03.2020.
//
#include <bits/stdc++.h>

#include <utility>

using namespace std;

unsigned int hsh(const string &x) {
    unsigned int res = 0;
    for (size_t i = 0; i < x.size(); i++) {
        res *= 37;
        res += x[i] + 7 * (i & 1);
    }
    return res % 100000;
}

typedef struct element {
    string key, val;
    element *next, *prev;
    bool del;

    element(string key, string val, element* prev) {
        this->key = std::move(key);
        this->val = std::move(val);
        this->del = false;
        this->next = nullptr;
        this->prev = prev;
    }
} el;

vector<element*> table[100000];

el *find(unsigned int x, const string &key) {
    for (auto &i : table[x]) {
        if (i->key == key) {
            return i;
        }
    }
    return nullptr;
}

int main() {
    ifstream in("linkedmap.in");
    ofstream out("linkedmap.out");

    string command;
    string key, val;
    el *last = nullptr;
    while (in >> command >> key) {
        unsigned int x = hsh(key);
        el *cur = find(x, key);

        if (command == "put") {
            in >> val;
            if (cur != nullptr) {
                cur->val = val;
                if (cur->del) {
                    cur->del = false;
                    cur->prev = last;
                    cur->next = nullptr;
                    if (last != nullptr) {
                        last->next = cur;
                    }
                    last = cur;
                }
            } else {
                cur = new el(key, val, last);
                table[x].push_back(cur);
                if (last != nullptr) {
                    last->next = cur;
                }
                last = cur;
            }
        }

        if (command == "delete") {
            if (cur != nullptr) {
                cur->del = true;
                if (last == cur) {
                    last = last->prev;
                }
                if (cur->prev != nullptr) {
                    cur->prev->next = cur->next;
                }
                if (cur->next != nullptr) {
                    cur->next->prev = cur->prev;
                }
                cur->next = nullptr;
                cur->prev = nullptr;
            }
        }

        if (command == "get") {
            if (cur != nullptr && !cur->del) {
                out << cur->val << "\n";
            } else {
                out << "none\n";
            }
        }
        if (command == "prev") {
            if (cur != nullptr && !cur->del && cur->prev != nullptr) {
                out << cur->prev->val << "\n";
            } else {
                out << "none\n";
            }
        }
        if (command == "next") {
            if (cur != nullptr && !cur->del && cur->next != nullptr) {
                out << cur->next->val << "\n";
            } else {
                out << "none\n";
            }
        }
    }
    in.close();
    out.close();
    return 0;
}
