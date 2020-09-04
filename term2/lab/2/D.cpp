//
// Created by covariance on 20.03.2020.
//
#include <bits/stdc++.h>

#define fs first
#define sc second

using namespace std;

const int OUTER_MOD = 50000;
const int INNER_MOD = 500;
ifstream in("multimap.in");
ofstream out("multimap.out");

unsigned int hsh(const string &x, const int mod) {
    unsigned int res = 0;
    for (size_t i = 0; i < x.size(); i++) {
        res *= 37;
        res += x[i] + 7 * (i & 1);
    }
    return res % mod;
}

struct st {
    vector<vector<pair<string, bool>>> table;
    size_t size;

    st() {
        this->table.resize(INNER_MOD);
        this->size = 0;
    }

    void insert(const string &val) {
        unsigned int x = hsh(val, INNER_MOD);
        for (auto &i : table[x]) {
            if (i.fs == val) {
                if (!i.sc) {
                    this->size++;
                    i.sc = true;
                }
                return;
            }
        }
        this->size++;
        table[x].emplace_back(val, true);
    }

    void remove(const string &val) {
        unsigned int x = hsh(val, INNER_MOD);
        for (auto &i : table[x]) {
            if (i.fs == val) {
                if (i.sc) {
                    this->size--;
                    i.sc = false;
                }
                return;
            }
        }
    }

    void clear() {
        this->size = 0;
        this->table.clear();
    }

    void print() {
        out << this->size;
        for (auto &i : table) {
            for (auto &j : i) {
                if (j.sc) {
                    out << " " << j.fs;
                }
            }
        }
        out << "\n";
    }
};

struct multmap {
    vector<vector<pair<string, st>>> table;

    multmap() {
        this->table.resize(OUTER_MOD);
    }

    st *find(const string &key, unsigned int x) {
        for (auto &i : table[x]) {
            if (i.fs == key) {
                return &i.sc;
            }
        }
        return nullptr;
    }

    void insert(const string &key, const string &val) {
        unsigned int x = hsh(key, OUTER_MOD);
        st *element = find(key, x);
        if (element != nullptr) {
            element->insert(val);
        } else {
            st tmp;
            tmp.insert(val);
            table[x].emplace_back(key, tmp);
        }
    }

    void remove(const string &key, const string &val) {
        unsigned int x = hsh(key, OUTER_MOD);
        st *element = find(key, x);
        if (element != nullptr) {
            element->remove(val);
        }
    }

    void removeAll(const string &key) {
        unsigned int x = hsh(key, OUTER_MOD);
        st *element = find(key, x);
        if (element != nullptr) {
            element->clear();
        }
    }

    void get(const string &key) {
        unsigned int x = hsh(key, OUTER_MOD);
        st *element = find(key, x);
        if (element != nullptr) {
            element->print();
        } else {
            out << "0\n";
        }
    }
};

int main() {
//    in.tie(nullptr);
//    out.tie(nullptr);
//    ios_base::sync_with_stdio(false);


    multmap mp;
    string command;
    string key, val;
    while (in >> command >> key) {
        if (command == "put") {
            in >> val;
            mp.insert(key, val);
        }
        if (command == "delete") {
            in >> val;
            mp.remove(key, val);
        }
        if (command == "deleteall") {
            mp.removeAll(key);
        }
        if (command == "get") {
            mp.get(key);
        }
    }

    in.close();
    out.close();
    return 0;
}
