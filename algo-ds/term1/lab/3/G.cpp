#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

const int inf = 2147483647;

vector<vector<int>> l, r;
vector<int> val;

vector<int> pointer;
vector< pair<int, size_t> > heap(1);
size_t sz = 0;

void siftUp(size_t ind) {
    if (ind != 1 && heap[ind].fs > heap[ind / 2].fs) {
        swap(heap[ind], heap[ind / 2]);
        swap(pointer[heap[ind].sc], pointer[heap[ind / 2].sc]);
        siftUp(ind / 2);
    }
}

void siftDown(size_t ind) {
    if (sz == 2 * ind) {
        if (heap[ind].fs < heap[2 * ind].fs) {
            swap(heap[ind], heap[2 * ind]);
            swap(pointer[heap[ind].sc], pointer[heap[2 * ind].sc]);
        }
    }
    if (sz > 2 * ind) {
        if (heap[ind].fs < max(heap[2 * ind].fs, heap[2 * ind + 1].fs)) {
            if (heap[2 * ind].fs > heap[2 * ind + 1].fs) {
                swap(heap[ind], heap[2 * ind]);
                swap(pointer[heap[ind].sc], pointer[heap[2 * ind].sc]);
                siftDown(2 * ind);
            } else {
                swap(heap[ind], heap[2 * ind + 1]);
                swap(pointer[heap[ind].sc], pointer[heap[2 * ind + 1].sc]);
                siftDown(2 * ind + 1);
            }
        }
    }
}

void push(pair<int, size_t> val) {
    sz++;
    if (heap.size() < sz + 1) {
        heap.push_back(val);
    } else {
        heap[sz] = val;
    }
    pointer[val.sc] = sz;
    siftUp(sz);
}

void deleteElement(size_t ind) {
    ind = pointer[ind];
    swap(heap[ind], heap[sz]);
    swap(pointer[heap[ind].sc], pointer[heap[sz].sc]);
    sz--;
    siftUp(ind);
    siftDown(ind);
}

void printHeap() {
    cout << sz <<endl;
    for (size_t i = 1; i <= sz; i++) {
        cout << heap[i].fs << ' ' <<heap[i].sc <<'\t';
    }
    cout <<endl;
}

int mx() {
    return heap[1].fs;
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    l.resize(n);
    r.resize(n);
    val.resize(m);
    pointer.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> val[i];
        l[a - 1].push_back(i);
        r[b - 1].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < l[i].size(); j++) {
            push(make_pair(val[l[i][j]], l[i][j]));
        }
        cout << ((sz == 0) ? inf : mx()) << ' ';
        for (size_t j = 0; j < r[i].size(); j++) {
            deleteElement(r[i][j]);
        }
    }
	return 0;
}
