#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node *prev;
    struct Node *next;
};
struct Head
{
    int len;
    struct Node *next;
};
typedef struct Head list;
typedef struct Node node;

void InitList(list **l);
void DestroyList(list *l);
void ListInsert(list *l);
void ListDelete(list *l, int pos, int *e);

int main()
{
    return 0;
}

void InitList(list **l)
{
    *l = (list *)malloc(sizeof(list));
    if (!(*l))
    {
        fprintf(stderr, "Cannot Initialize List\n");
        return;
    }
    (*l)->len = 0;
    (*l)->next = NULL;
    return;
}
void DestroyList(list *l)
{
    if (l->len)
    {
        node *cur = l->next;
        for (int i = 0; i < l->len - 1; i++)
        {
            node *nxt = cur->next;
            free(cur);
            cur = nxt;
        }
        free(cur);
    }
    free(l);
    return;
}