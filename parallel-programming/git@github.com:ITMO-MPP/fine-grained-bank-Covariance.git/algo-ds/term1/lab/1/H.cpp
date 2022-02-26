#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

struct manual_queue {
    int head, cap, size;
    int* arr;
};

typedef struct manual_queue que;

void que_create(que* q) {
    q->size = 0;
    q->head = 0;
    q->cap = 1;
    q->arr = (int*)malloc(sizeof(int));
}

void que_push_back(que* q, int val) {
    if (q->size == q->cap) {
        int* new_arr = (int*)malloc(2*(q->cap)*sizeof(int));
        for (int i = 0; i < q->cap; i++) {
            new_arr[i] = (q->arr)[(i+q->head)%(q->cap)];
        }
        free(q->arr);
        q->arr = new_arr;
        q->head = 0;
        q->cap*=2;
    }
    (q->arr)[(q->head + q->size)%(q->cap)] = val;
    q->size++;
}

int que_pop_front(que* q) {
    int retv = (q->arr)[q->head];
    q->head = (q->head+1)%(q->cap);
    q->size--;
    return retv;
}

void que_clear(que* q) {
    free(q->arr);
    que_create(q);
}
int main() {
    que q, labels;
    que_create(&q);
    que_create(&labels);
    string prog[100007];
    int reg[26];
    int cnt = 0, a, b, j;
    while (cin >> prog[cnt]) {
            cnt++;
    }
    for (int i = 0; i < cnt; i++) {
        if (prog[i][0] == ':') {
            bool currentlyExists = false;
            for (j = 0; j < labels.size; j++) {
                    if ((labels.arr)[j] == i) {
                            currentlyExists = true;
                    }
            }
            if (!currentlyExists) {
                    que_push_back(&labels, i);
            }
        }
    }
    for (int i = 0; i < cnt; i++) {
        if (prog[i][0] == '+') {
            a = que_pop_front(&q);
            b = que_pop_front(&q);
            que_push_back(&q, (a+b)%65536);
            continue;
        }

        if (prog[i][0] == '-') {
            a = que_pop_front(&q);
            b = que_pop_front(&q);
            que_push_back(&q, int((unsigned short) (a-b)));
            continue;
        }

        if (prog[i][0] == '*') {
            a = que_pop_front(&q);
            b = que_pop_front(&q);
            que_push_back(&q, int((unsigned short) (((long long)(a)) * ((long long)(b)))));
            continue;
        }

        if (prog[i][0] == '/') {
            a = que_pop_front(&q);
            b = que_pop_front(&q);
            if (b != 0) {
                que_push_back(&q, int((unsigned short) (a/b)));
            } else {
                que_push_back(&q, 0);
            }
            continue;
        }

        if (prog[i][0] == '%') {
            a = que_pop_front(&q);
            b = que_pop_front(&q);
            if (b != 0) {
                que_push_back(&q, int((unsigned short) (a%b)));
            } else {
                que_push_back(&q, 0);
            }
            continue;
        }

        if (prog[i][0] == '>') {
            a = que_pop_front(&q);
            reg[int(prog[i][1] - 'a')] = a;
            continue;
        }

        if (prog[i][0] == '<') {
            que_push_back(&q, reg[int(prog[i][1] - 'a')]);
            continue;
        }

        if (prog[i][0] == 'P') {
            if (prog[i].length() == 1) {
                a = que_pop_front(&q);
                cout << a << "\n";
            } else {
                cout << reg[int(prog[i][1] - 'a')] << "\n";
            }
            continue;
        }

        if (prog[i][0] == 'C') {
            if (prog[i].length() == 1) {
                a = que_pop_front(&q);
                cout << char(a % 256);
            } else {
                cout << char(reg[int(prog[i][1] - 'a')] % 256);
            }
            continue;
        }

        if (prog[i][0] == 'J') {
            for (j = 0; j < labels.size; j++) {
                if (prog[i].substr(1).compare(prog[(labels.arr)[j]].substr(1)) == 0) {
                    break;
                }
            }
            i = (labels.arr)[j];
            continue;
        }

        if (prog[i][0] == 'Z') {
            if (reg[int(prog[i][1] - 'a')] == 0) {
                for (j = 0; j < labels.size; j++) {
                    if (prog[i].substr(2).compare(prog[(labels.arr)[j]].substr(1)) == 0) {
                        break;
                    }
                }
                i = (labels.arr)[j];
            }
            continue;
        }

        if (prog[i][0] == 'E') {
            if (reg[int(prog[i][1] - 'a')] == reg[int(prog[i][2] - 'a')]) {
                for (j = 0; j < labels.size; j++) {
                    if (prog[i].substr(3).compare(prog[(labels.arr)[j]].substr(1)) == 0) {
                        break;
                    }
                }
                i = (labels.arr)[j];
            }
            continue;
        }

        if (prog[i][0] == 'G') {
            if (reg[int(prog[i][1] - 'a')] > reg[int(prog[i][2] - 'a')]) {
                for (j = 0; j < labels.size; j++) {
                    if (prog[i].substr(3).compare(prog[(labels.arr)[j]].substr(1)) == 0) {
                        break;
                    }
                }
                i = (labels.arr)[j];
            }
            continue;
        }

        if (prog[i][0] == 'Q') {
            return 0;
        }
        if ((int('0') <= prog[i][0]) && (prog[i][0] <= int('9'))) {
            que_push_back(&q, stoi(prog[i]));
            continue;
        }
    }
    return 0;
}
