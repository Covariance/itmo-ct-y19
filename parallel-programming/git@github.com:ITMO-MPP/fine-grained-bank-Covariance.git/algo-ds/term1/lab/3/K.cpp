#include <bits/stdc++.h>

using namespace std;

bool debug = false;

const int MIN_INF = -2147483648;
const int MAX_INF = 2147483647;

struct node {
    pair<int, size_t> value;
    size_t heapIndex;
    node *parent, *child, *nextBrother;

    node(pair<int, size_t> value, size_t heapIndex) {
        this->heapIndex = heapIndex;
        this->value = value;
        this->child = nullptr;
        this->nextBrother = nullptr;
        this->parent = nullptr;
    }
};

struct binomialHeap {
    vector<node*> lst;

    binomialHeap() {
        this->lst.resize(0);
    }

    binomialHeap(node *head) {
        this->lst.resize(1);
        this->lst[0] = head;
    }
};

vector<node*> ind;
vector<bool> deleted;
vector<binomialHeap> arr;

void dfs(node* a) {
    if (a == nullptr) return;
    cout <<"(" <<a->value.first <<"; " <<a->value.second << ") ";
    dfs(a->child);
    dfs(a->nextBrother);
}

void printHeap(binomialHeap a) {
    for (size_t i = 0; i < a.lst.size(); i++) {
        cout << "tree number " <<i <<": ";
        dfs(a.lst[i]);
        cout << endl;
    }
    cout <<"finish\n";
}

pair<node*, size_t> getMin(binomialHeap h) {
    size_t index = 0;
    pair<int, size_t> mn = make_pair(MAX_INF, (size_t)MAX_INF);
    node* retv = h.lst[0];
    for (size_t i = 0; i < h.lst.size(); i++) {
        if (h.lst[i] != nullptr &&
             ((h.lst[i]->value.first < mn.first) ||
              (h.lst[i]->value.first == mn.first && h.lst[i]->value.second < mn.second))) {
            retv = h.lst[i];
            mn = h.lst[i]->value;
            index = i;
        }
    }
    return make_pair(retv, index);
}

size_t getHeapIndex(node* a) {
    while (a->parent != nullptr) {
        a = a->parent;
    }
    return a->heapIndex;
}

node* lastBrother(node* a) {
    while (a->nextBrother != nullptr) {
        a = a->nextBrother;
    }
    return a;
}

node* sum(node* a, node* b) {
    if ( (a->value.first >  b->value.first) ||
         (a->value.first == b->value.first && a->value.second > b->value.second)) {
        swap(a, b);
    }
    if (a->child == nullptr) {
        a->child = b;
    } else {
        lastBrother(a->child)->nextBrother = b;
    }
    b->parent = a;
    return a;
}

binomialHeap merge(binomialHeap a, binomialHeap b) {
    binomialHeap res;
    if (a.lst.size() < b.lst.size()) {
        swap(a, b);
    }
    node* transfer = nullptr;
    for (size_t i = 0; i < a.lst.size(); i++) {
        if (transfer == nullptr) {
            if (a.lst[i] != nullptr) {
                if ((i >= b.lst.size() ? nullptr : b.lst[i]) != nullptr) {     /// Переноса нет, 1 1
                    res.lst.push_back(nullptr);
                    transfer = sum(a.lst[i], b.lst[i]);
                } else {    /// Переноса нет, 1 0
                    res.lst.push_back(a.lst[i]);
                }
            } else {
                if ((i >= b.lst.size() ? nullptr : b.lst[i]) != nullptr) {     /// Переноса нет, 0 1
                    res.lst.push_back(b.lst[i]);
                } else {    /// Переноса нет, 0 0
                    res.lst.push_back(nullptr);
                }
            }
        } else {
            if (a.lst[i] != nullptr) {
                if ((i >= b.lst.size() ? nullptr : b.lst[i]) != nullptr) {     /// Перенос есть, 1 1
                    res.lst.push_back(transfer);
                    transfer = sum(a.lst[i], b.lst[i]);
                } else {    /// Перенос есть, 1 0
                    res.lst.push_back(nullptr);
                    transfer = sum(transfer, a.lst[i]);
                }
            } else {
                if ((i >= b.lst.size() ? nullptr : b.lst[i]) != nullptr) {     /// Перенос есть, 0 1
                    res.lst.push_back(nullptr);
                    transfer = sum(transfer, b.lst[i]);
                } else {    /// Перенос есть, 0 0
                    res.lst.push_back(transfer);
                    transfer = nullptr;
                }
            }
        }
    }
    if (transfer != nullptr) {
        res.lst.push_back(transfer);
    }
    return res;
}

void add(size_t heapIndex, pair<int, size_t> value) {
    node *b = new node(value, heapIndex);
    if (value.second == ind.size()) {
        ind.push_back(b);
        deleted.push_back(false);
    } else {
        ind[value.second] = b;
        deleted[value.second] = false;
    }
    arr[heapIndex] = merge(arr[heapIndex], *(new binomialHeap(b)));
}

void siftUp(node *a) {
    while (a->parent != nullptr) {
        swap(ind[a->value.second], ind[a->parent->value.second]);
        swap(a->value, a->parent->value);
        a = a->parent;
    }
}

int extractMin(binomialHeap *a) {
    binomialHeap tmp = *new binomialHeap();
    pair<node*, size_t> extracted = getMin(*a);
    int retv = extracted.first->value.first;
    a->lst[extracted.second] = nullptr;
    if (extracted.first->child != nullptr) {
        node* child = extracted.first->child;
        while (child != nullptr) {
            tmp.lst.push_back(child);
            child->heapIndex = extracted.first->heapIndex;
            child = child->nextBrother;
            tmp.lst[tmp.lst.size() - 1]->nextBrother = nullptr;
            tmp.lst[tmp.lst.size() - 1]->parent = nullptr;
        }
        *a = merge(*a, tmp);
    }
    return retv;
}

size_t del(size_t index) {
    deleted[index] = true;
    ind[index]->value = make_pair(MIN_INF, ind[index]->value.second);
    siftUp(ind[index]);
    size_t retv = getHeapIndex(ind[index]);
    extractMin(&arr[retv]);
    return retv;
}

void changeKey(pair<int, size_t> value) {
    add(del(value.second), value);
}

int main() {
    int n, m, t, a, b;
    size_t cnt = 0;
    cin >> n >> m;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        arr[i] = *(new binomialHeap());
    }
    for (int i = 0; i < m; i++) {
        cin >> t;
        if (t == 0) {
            cin >> a >> b;
            add((size_t)(a - 1), make_pair(b, cnt++));
        }
        if (t == 1) {
            cin >> a >> b;
            arr[b - 1] = merge(arr[b - 1], arr[a - 1]);
            arr[a - 1] = *(new binomialHeap());
            for (size_t j = 0; j < arr[b - 1].lst.size(); j++) {
                if (arr[b - 1].lst[j] != nullptr) {
                    arr[b - 1].lst[j]->heapIndex = (size_t)(b - 1);
                }
            }
        }
        if (t == 2) {
            cin >> a;
            if (!deleted[(size_t)(a - 1)]) {
                del((size_t)(a - 1));
            }
        }
        if (t == 3) {
            cin >> a >> b;
            changeKey(make_pair(b, (size_t)(a - 1)));
        }
        if (t == 4) {
            cin >> a;
            cout << getMin(arr[a - 1]).first->value.first <<"\n";
        }
        if (t == 5) {
            cin >> a;
            extractMin(&arr[a - 1]);
        }
        if (t == 6) {
            cin >> a;
            printHeap(arr[a - 1]);
        }
        if (t == 7) {
            for (size_t j = 0; j < cnt; j++) {
                cout << ind[j] << endl;
            }
        }
    }
    return 0;
}
