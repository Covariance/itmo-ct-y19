#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_LEN = 50000;

struct manual_vector
{
    int cap;
    int cur;
    int* arr;
};
typedef struct manual_vector vec;

void vec_create(vec* v)
{
    v->cap = 1;
    v->cur = 0;
    v->arr = (int*)malloc(sizeof(int));
}

void vec_push_back(vec* v, int val)
{
    if (v->cap == v->cur)
    {
        int* new_arr = (int*)malloc(2*(v->cap)*sizeof(int));
        for (; v->cur >= 0; v->cur--) new_arr[v->cur] = (v->arr)[v->cur];
        v->cur = v->cap;
        v->cap*=2;
        free(v->arr);
        v->arr = new_arr;
    }
    (v->arr)[v->cur] = val;
    v->cur++;
}

int vec_pop_back(vec* v)
{
    v->cur--;
    return (v->arr)[v->cur];
}

int vec_get(vec* v, int i)
{
    return (v->arr)[i];
}

int vec_top(vec* v)
{
    return (v->arr)[v->cur-1];
}

void vec_clear(vec* v)
{
    free(v->arr);
    vec_create(v);
}

int main()
{
    vec v;
    vec_create(&v);

    char c;
    while (scanf(" %c", &c) == 1)
    {
        if (c == '+')
        {
            int a, b;
            a = vec_top(&v);
            vec_pop_back(&v);
            b = vec_top(&v);
            vec_pop_back(&v);
            vec_push_back(&v, a+b);
        }

        if (c == '-')
        {
            int a, b;
            a = vec_top(&v);
            vec_pop_back(&v);
            b = vec_top(&v);
            vec_pop_back(&v);
            vec_push_back(&v, b-a);
        }

        if (c == '*')
        {
            int a, b;
            a = vec_top(&v);
            vec_pop_back(&v);
            b = vec_top(&v);
            vec_pop_back(&v);
            vec_push_back(&v, a*b);
        }

        if (47 < (int)c && (int)c < 58) vec_push_back(&v, (int)c - 48);
    }

    printf("%d", vec_top(&v));
    return 0;
}
