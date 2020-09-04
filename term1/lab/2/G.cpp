#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
const int BLOCK_LEN = 8;
const int BLOCK_NUM = 32/BLOCK_LEN;
const int BLOCK_SIZE = 1 << BLOCK_LEN;

int n, t;
uint cur = 0, a, b;
vector<uint> arr;
vector<uint> tmp;
vector<int> index[BLOCK_SIZE];

void setup() {
    cin >> t >> n >> a >> b;
    arr.resize(n);
    tmp.resize(n);
}

uint getBlock(uint a, int i) {
    return ((a >> (BLOCK_LEN * i))%BLOCK_SIZE);
}

uint nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

uint nextRand32() {
    uint a = nextRand24(), b = nextRand24();
    return (a << 8)^b;
}


void readTest() {
    for (int i = 0; i < n; i++) {
        arr[i] = nextRand32();
    }
}

void linearSort() {
    for (int i = 0; i < BLOCK_NUM; i++) {
        for (int j = 0; j < n; j++) {
            index[getBlock(arr[j], i)].push_back(j);
        }
        int curPos = 0;
        for (int j = 0; j < BLOCK_SIZE; j++) {
            for (uint k = 0; k < index[j].size(); k++) {
                tmp[curPos] = arr[index[j][k]];
                curPos++;
            }
            index[j].clear();
        }
        for (int j = 0; j < n; j++) {
            arr[j] = tmp[j];
        }
    }
}

void printArray() {
    ull sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (ull)(arr[i]) * (ull)(i + 1);
    }
    cout << sum <<'\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setup();
    for (int i = 0; i < t; i++) {
        readTest();
        linearSort();
        printArray();
    }
    return 0;
}
