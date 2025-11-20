#include <stdio.h>
#include <string.h>

typedef int Elem;
typedef struct CSNode
{
    Elem data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

void Enqueue(CSTree t) {}
CSTree Dequeue(void) {}
int IsEmptyQueue(void) {}

void PreOdTra(CSTree t)
{
    if (!t)
        return;
    printf("%d ", t->data);
    PreOdTra(t->firstchild);
    PreOdTra(t->nextsibling);
}

void LevOdTra(CSTree t)
{
    Enqueue(t);
    while (!IsEmptyQueue())
    {
        CSTree head = Dequeue();
        printf("%d ", head->data);
        for (CSTree c = head->firstchild; c; c = c->nextsibling)
            Enqueue(c);
    }
    return;
}

int main()
{
    return 0;
}