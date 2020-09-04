#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct manual_queue
{
    int head, cap, size;
    int* arr;
};

typedef struct manual_queue que;

void que_create(que* q)
{
    q->size = 0;
    q->head = 0;
    q->cap = 1;
    q->arr = (int*)malloc(sizeof(int));
}

void que_push_back(que* q, int val)
{
    if (q->size == q->cap)
    {
        int* new_arr = (int*)malloc(2*(q->cap)*sizeof(int));
        for (int i = 0; i < q->cap; i++)
            new_arr[i] = (q->arr)[(i+q->head)%(q->cap)];
        free(q->arr);
        q->arr = new_arr;
        q->head = 0;
        q->cap*=2;
    }
    (q->arr)[(q->head + q->size)%(q->cap)] = val;
    q->size++;
}

int que_pop_front(que* q)
{
    int retv = (q->arr)[q->head];
    q->head = (q->head+1)%(q->cap);
    q->size--;
    return retv;
}

void que_clear(que* q)
{
    free(q->arr);
    que_create(q);
}

int main()
{
    int n;
    scanf("%d", &n);

    que q;
    que_create(&q);

    for (int i = 0; i < n; i++)
    {
        char c;
        scanf(" %c", &c);

        if (c == '+')
        {
            int a;
            scanf(" %d\n", &a);
            que_push_back(&q, a);
        }
        if (c == '-')
            printf("%d\n", que_pop_front(&q));
    }

    que_clear(&q);
    return 0;
}
