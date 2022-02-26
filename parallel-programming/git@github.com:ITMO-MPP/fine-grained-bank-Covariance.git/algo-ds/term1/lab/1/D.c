#include <stdio.h>
#include <stdlib.h>

struct list_element
{
    struct list_element* next;
    int val;
};

typedef struct list_element lste;

int main()
{

    int n;
    scanf("%d", &n);

    lste* top = NULL;
    lste* bot = NULL;

    for (int i = 0; i < n; i++)
    {
        char c;
        scanf(" %c", &c);

        if (c == '+')
        {
            int a;
            scanf(" %d\n", &a);

            lste* new_top = (lste*)malloc(sizeof(lste));
            new_top->val = a;
            new_top->next = NULL;
            if (top == NULL)
            {
                top = new_top;
                bot = new_top;
            }
            else
            {
                top->next = new_top;
                top = new_top;
            }
        }
        if (c == '-')
        {
            printf("%d\n", bot->val);
            lste* erased = bot;
            bot = bot->next;
            if (bot == NULL) top = NULL;
            free(erased);
        }
    }

    while(bot != NULL)
    {
        lste* erased = bot;
        bot = bot->next;
        free(erased);
    }

    return 0;
}
