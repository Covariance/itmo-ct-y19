#include <stdio.h>
#include <stdlib.h>

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

void push_back(vec* v, int val)
{
    if(v->cap == v->cur)
    {
        int* new_arr = (int*)malloc(2*(v->cap)*sizeof(int));
        for(; v->cur >= 0; v->cur--) new_arr[v->cur] = (v->arr)[v->cur];
        v->cur = v->cap;
        v->cap*=2;
        free(v->arr);
        v->arr = new_arr;
    }
    (v->arr)[v->cur] = val;
    v->cur++;
}

int pop_back(vec* v)
{
    v->cur--;
    return (v->arr)[v->cur];
}

int get(vec* v, int i)
{
    return (v->arr)[i];
}

void vec_clear(vec* v)
{
    free(v->arr);
}

int main()
{
    int n;
    scanf("%d", &n);

    vec v;
    vec_create(&v);

    for (int i = 0; i < n; i++)
    {
        char c;
        scanf(" %c", &c);

        if (c == '+')
        {
            int a;
            scanf(" %d\n", &a);
            push_back(&v, a);
        }
        if (c == '-') printf("%d\n", pop_back(&v));
    }

    vec_clear(&v);
    return 0;
}
