#include <stdio.h>
#include <stdlib.h>
#pragma gcc optimize("O3");
typedef long long ll;

struct min_vector{
    int cap;
    int cur;
    int* arr;
    int* min_arr;
};
typedef struct min_vector vec;

ll a, b, c, xp, xpp, x[1000];
int k, pos = 0;

int min(int a, int b) {
    if(a > b) return b;
    return a;
}

int quest_get_next() {
    if (pos < k) return x[pos++];
    int retv = (int)(a*xpp + b*xp + c);
    xpp = xp;
    xp = retv;
    pos++;
    return retv;
}

void vec_create(vec* v) {
    v->cap = 1;
    v->cur = 0;
    v->arr = (int*)malloc(sizeof(int));
    v->min_arr = (int*)malloc(sizeof(int));
}

void push_back(vec* v, int val) {
    if(v->cap == v->cur)
    {
        int* new_arr = (int*)malloc(2*(v->cap)*sizeof(int));
        int* new_min_arr = (int*)malloc(2*(v->cap)*sizeof(int));
        for(; v->cur >= 0; v->cur--) {
                new_arr[v->cur] = (v->arr)[v->cur];
                new_min_arr[v->cur] = (v->min_arr)[v->cur];
        }
        v->cur = v->cap;
        v->cap*=2;
        free(v->arr);
        free(v->min_arr);
        v->arr = new_arr;
        v->min_arr = new_min_arr;
    }
    (v->arr)[v->cur] = val;
    (v->min_arr)[v->cur] = (v->cur == 0) ? val : min((v->min_arr)[v->cur - 1], val);
    v->cur++;
}

int pop_back(vec* v) {
    v->cur--;
    return (v->arr)[v->cur];
}

int get_min(vec* v) {
    return (v->min_arr)[v->cur - 1];
}

void vec_clear(vec* v) {
    free(v->arr);
}

struct min_queue{
    vec* s1;
    vec* s2;
};
typedef struct min_queue que;

int pop(que* q) {
    if (q->s1->cur == 0) {
        int expand = 1;
        while (expand * q->s1->cap < q->s2->cur) expand *= 2;
        if (q->s1->cap < q->s2->cur) {
            free(q->s1->arr);
            free(q->s1->min_arr);
            q->s1->arr = (int*)malloc(expand*(q->s1->cap)*sizeof(int));
            q->s1->min_arr = (int*)malloc(expand*(q->s1->cap)*sizeof(int));
        }
        while (q->s2->cur > 0) {
            push_back(q->s1, pop_back(q->s2));
        }
    }
    return pop_back(q->s1);
}

void push(que* q, int val) {
    push_back(q->s2, val);
}

void que_print(que* q) {
    for(int i = q->s1->cur - 1; i >= 0; i--) printf("%intd ", (q->s1->arr)[i]);
    for(int i = 0; i < q->s2->cur; i++) printf("%intd ", (q->s2->arr)[i]);
}

int que_get_min(que* q) {
    if (q->s1->cur == 0) return get_min(q->s2);
    if (q->s2->cur == 0) return get_min(q->s1);
    return min(get_min(q->s1), get_min(q->s2));
}

int main() {

    que q;
    vec s1, s2;
    vec_create(&s1);
    vec_create(&s2);
    q.s1 = &s1;
    q.s2 = &s2;
    int n, m;
    ll sum = 0;
    scanf("%d %d %d\n", &n, &m, &k);
    scanf("%d %d %d\n", &a, &b, &c);
    for (int i = 0; i < k; i++) scanf("%lld", &x[i]);
    xp = x[k-1];
    xpp = x[k-2];
    for (int i = 0; i < m; i++) {
        push(&q, quest_get_next());
    }
    for (int i = 0; i < n - m + 1; i++) {
        sum += que_get_min(&q);
        pop(&q);
        push(&q, quest_get_next());
    }
    printf("%lld", sum);
    return 0;
}
