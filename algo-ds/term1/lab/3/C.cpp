#include <bits/stdc++.h>
#define fs first
#define sc second

using namespace std;

bool debug = false;

vector<int> pointer;
vector<int> extracted;
vector< pair<int, size_t> > heap(1);
size_t sz = 0;

void siftUp(size_t ind) {
    if (ind != 1 && heap[ind].fs < heap[ind / 2].fs) {
        swap(heap[ind], heap[ind / 2]);
        swap(pointer[heap[ind].sc], pointer[heap[ind / 2].sc]);
        siftUp(ind / 2);
    }
}

void siftDown(size_t ind) {
    if (sz == 2 * ind) {
        if (heap[ind].fs > heap[2 * ind].fs) {
            swap(heap[ind], heap[2 * ind]);
            swap(pointer[heap[ind].sc], pointer[heap[2 * ind].sc]);
        }
    }
    if (sz > 2 * ind) {
        if (heap[ind].fs > min(heap[2 * ind].fs, heap[2 * ind + 1].fs)) {
            if (heap[2 * ind].fs < heap[2 * ind + 1].fs) {
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
    extracted[val.sc] = false;
    siftUp(sz);
}

void deleteElement(size_t ind) {
    extracted[heap[ind].sc] = true;
    swap(heap[ind], heap[sz]);
    swap(pointer[heap[ind].sc], pointer[heap[sz].sc]);
    sz--;
    siftDown(ind);
    siftUp(ind);
}

pair<int, size_t> extractMin() {
    swap(heap[1], heap[sz]);
    swap(pointer[heap[1].sc], pointer[heap[sz].sc]);
    sz--;
    siftDown(1);
    return heap[sz + 1];
}

void printHeap() {
    for (size_t i = 1; i <= sz; i++) {
        cout << heap[i].fs << ' ';
    }
    cout <<endl;
}

int main() {
    int a, b;
    string s;
    size_t opCnt = 0;
    while (cin >> s) {
        pointer.push_back(-1);
        extracted.push_back(true);
        if (s[0] == 'p') {
            cin >> a;
            push(make_pair(a, opCnt));
        }
        if (s[0] == 'e') {
            if (sz == 0) {
                cout <<"*\n";
            } else {
                pair<int, size_t> retv = extractMin();
                cout << retv.fs << ' ' << retv.sc + 1 <<"\n";
            }
        }
        if (s[0] == 'd') {
            cin >> a >> b;
            if (!extracted[a - 1]) {
                deleteElement(pointer[a - 1]);
                push(make_pair(b, a - 1));
            }
        }
        opCnt++;
    }
    return 0;
}
