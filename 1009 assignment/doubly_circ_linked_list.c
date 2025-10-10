#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    struct Node *prev;
    struct Node *next;
};
typedef struct Node node;

void InitList(node **l);
void DestroyList(node **l);
void ListInsert(node *l, int pos, int e);
void ListDelete(node *l, int pos, int *e);
void DebugPrintList(node *l);
void Test(void);

int main()
{
    Test();
    return 0;
}

void InitList(node **l)
{
    *l = (node *)malloc(sizeof(node));
    if (!(*l))
    {
        fprintf(stderr, "Cannot Initialize List\n");
        return;
    }
    (*l)->val = 0;
    (*l)->next = NULL;
    (*l)->prev = NULL;
    return;
}
void DestroyList(node **l)
{
    if (*l == NULL)
        return;
    if ((*l)->val)
    {
        node *cur = (*l)->next;
        for (int i = 0; i < (*l)->val - 1; i++)
        {
            node *nxt = cur->next;
            free(cur);
            cur = nxt;
        }
        free(cur);
    }
    free(*l);
    *l = NULL;
    return;
}
void ListInsert(node *l, int pos, int e)
{
    node *ptr = (node *)malloc(sizeof(node));
    if (!ptr)
    {
        fprintf(stderr, "Cannot Allocte Space For New Node\n");
        return;
    }
    node *cur = l;
    if (pos - 1 > l->val || pos <= 0)
    {
        fprintf(stderr, "Illegal Position To Insert\n");
        return;
    }
    /* Detects the special case: inserting at the head of a non-empty list.
     * Transformation: Convert "insert at head" to an equivalent "insert after tail".
     * By changing pos to l->val + 1, cur point to the correct
     * predecessor for a head insertion in a circular list.
     */
    char flag = 0;
    if (pos == 1 && l->val)
    {
        pos += l->val;
        flag = 1;
    }
    for (int i = 0; i < pos - 1; i++)
        cur = cur->next;
    node *nxt = cur->next;
    cur->next = ptr;
    ptr->next = nxt;
    ptr->prev = cur;
    ptr->val = e;

    if (l->val == 0) // single node
    {
        ptr->prev = ptr;
        ptr->next = ptr;
    }
    if (pos == l->val + 1) // insert at tail
        l->next->prev = ptr;
    if (flag)
        l->next = ptr;
    l->val++;
    return;
}
void ListDelete(node *l, int pos, int *e)
{
    if (l->val == 0 || pos > l->val || pos <= 0)
    {
        fprintf(stderr, "Illegal Position To Delete\n");
        return;
    }
    if (l->val == 1)
    {
        *e = l->next->val;
        free(l->next);
        l->next = NULL;
        l->val--;
        return;
    }

    node *pvs = l->next;
    for (int i = 0; i < pos - 2; i++)
        pvs = pvs->next;
    if (pos == 1) // special
        pvs = pvs->prev;
    node *del = pvs->next;
    *e = del->val;
    node *nxt = del->next;
    pvs->next = nxt;
    nxt->prev = pvs;
    free(del);
    if (pos == 1) // special
        l->next = nxt;
    l->val--;
    return;
}
void DebugPrintList(node *l)
{
    if (l == NULL)
    {
        fprintf(stderr, "No Such Node List\n");
        return;
    }
    if (l->val == 0)
    {
        printf("Empty Node List\n");
        return;
    }
    node *cur = l->next;
    printf("From Head To Tail:");
    for (int i = 0; i < l->val; i++)
    {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    cur = l->next->prev;
    printf("\nFrom Tail To Head:");
    for (int i = 0; i < l->val; i++)
    {
        printf("%d ", cur->val);
        cur = cur->prev;
    }
    printf("\n");
    return;
}
void Test(void)
{
    node *l;
    int tmp;
    InitList(&l);
    ListInsert(l, 1, 1);
    DebugPrintList(l);
    ListInsert(l, 1, 2);
    DebugPrintList(l);
    ListInsert(l, 3, 3);
    DebugPrintList(l);
    ListInsert(l, 4, 5);
    DebugPrintList(l);
    ListInsert(l, 1, 4);
    DebugPrintList(l);
    ListDelete(l, 3, &tmp);
    DebugPrintList(l);
    ListDelete(l, 1, &tmp);
    DebugPrintList(l);
    DestroyList(&l);
    DebugPrintList(l);
    return;
}