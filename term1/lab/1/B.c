#include <stdio.h>
#include <stdlib.h>

struct list_element
{
    struct list_element* prev;
    int val;
};

typedef struct list_element lste;

void push_back(lste** cur, int added)
{
    lste* new_last = (lste*)malloc(sizeof(lste));
    new_last->val = added;
    new_last->prev = *cur;
    *cur = new_last;
}

int pop_back(lste** cur)
{
    int retv = (*cur)->val;
    lste* erased = *cur;
    *cur = (*cur)->prev;
    free(erased);
    return retv;
}

void clear_lst(lste** cur)
{
    while(*cur != NULL)
    {
        lste* erased = *cur;
        *cur = (*cur)->prev;
        free(erased);
    }
}

int main()
{

    int n;
    scanf("%d", &n);

    lste* cur = NULL;

    for (int i = 0; i < n; i++)
    {
        char c;
        scanf(" %c", &c);

        if (c == '+')
        {
            int a;
            scanf(" %d\n", &a);
            push_back(&cur, a);
        }
        if (c == '-')
            printf("%d\n", pop_back(&cur));
    }

    clear_lst(&cur);

    return 0;
}
