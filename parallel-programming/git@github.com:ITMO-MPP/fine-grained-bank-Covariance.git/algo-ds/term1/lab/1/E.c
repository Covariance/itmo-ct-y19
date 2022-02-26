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

    char str[MAX_LEN];

    while (1)
    {
        fgets(str, MAX_LEN, stdin);
        if (feof(stdin)) {
            break;
        }
        int check = 1;

        for (int i = 0; (i < strlen(str) && check == 1); i++)
        {
            if (str[i] == '(') vec_push_back(&v, 0);
            if (str[i] == '[') vec_push_back(&v, 1);

            if (str[i] == ')')
            {
                if (vec_top(&v) == 0) vec_pop_back(&v);
                else
                {
                    check = 0;
                    break;
                }
            }
            if (str[i] == ']')
            {
                if (vec_top(&v) == 1) vec_pop_back(&v);
                else
                {
                    check = 0;
                    break;
                }
            }
        }

        if (v.cur != 0) check = 0;
        if (check == 1) printf("YES\n");
        else printf("NO\n");
        vec_clear(&v);
    }
    return 0;
}
