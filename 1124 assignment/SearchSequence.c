#define NULL 0
typedef struct Node
{
    int data;
    int visit;
    struct Node *next;
} node;
typedef node *list;

/*With head node*/

int search(int dest, list l)
{
    node *cur = l->next;
    node *prev = l;
    while (cur)
    {
        if (cur->data == dest)
            break;
        prev = cur;
        cur = cur->next;
    }
    if (!cur)
        return 0;
    cur->visit++;
    if (prev == l || cur->visit <= prev->visit)
        return 1;

    prev->next = cur->next;
    node *pos = l;
    while (pos->next && pos->next->visit >= cur->visit)
        pos = pos->next;

    cur->next = pos->next;
    pos->next = cur;

    return 1;
}