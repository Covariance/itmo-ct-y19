#include <bits/stdc++.h>
using namespace std;

struct setGetStruct{
    int* original;
    int* iter;
    int* filled;
    int cap;
    int cnt;
}; typedef setGetStruct sgs;

void sgsCreate(sgs* a, int n)
{
    a->original = (int*)malloc(n*sizeof(int));
    a->iter = (int*)malloc(n*sizeof(int));
    a->filled = (int*)malloc(n*sizeof(int));
    a->cap = n;
    a->cnt = 0;
}

int sgsGet(sgs* a, int i)
{
    if ((a->iter)[i] >= a->cnt || (a->iter)[i] < 0 || (a->filled)[(a->iter)[i]] != i) return 0;
    return (a->original)[i];
}

void sgsSet(sgs* a, int i, int x)
{
    (a->original)[i] = x;
    if (a->cnt < a->cap && ((a->iter)[i] >= a->cnt || (a->iter)[i] < 0 || (a->filled)[(a->iter)[i]] != i)) {
        (a->iter)[i] = a->cnt;
        (a->filled)[a->cnt] = i;
        a->cnt++;
    }
}

int main() {
    int n;
    cin >>n;
    sgs arr;
    sgsCreate(&arr, n);
    int choice = 0;
    while (choice == 0 || choice == 1) {
        cout <<"0 to set(i, x);   1 to get(i);  anything else to break\n";
        cin >>choice;
        if (choice == 0) {
            int i, x;
            cin >>i >>x;
            sgsSet(&arr, i, x);
        }
        if (choice == 1) {
            int i;
            cin >>i;
            cout <<sgsGet(&arr, i) <<endl;
        }
    }
    return 0;
}
