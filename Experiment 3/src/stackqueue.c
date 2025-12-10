#include <stdlib.h>
#include "trie.h"
#include "trie_adt.h"
#include "stackqueue.h"

Queue *createQueue(void)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isEmpty(Queue *q)
{
    return q->front == NULL;
}
void enqueue(Queue *q, tset val)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->data = val;
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

tset dequeue(Queue *q)
{
    if (isEmpty(q))
        return NULL;
    QueueNode *temp = q->front;
    tset val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return val;
}

void destroyQueue(Queue *q)
{
    while (!isEmpty(q))
    {
        dequeue(q);
    }
    free(q);
}

pstack *createPStack(void)
{
    pstack *s = (pstack *)malloc(sizeof(pstack));
    s->top = NULL;
    return s;
}

void pushPStack(pstack *s, tset val)
{
    PStackNode *newNode = (PStackNode *)malloc(sizeof(PStackNode));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

tset popPStack(pstack *s)
{
    if (isEmptyPStack(s))
        return NULL;
    PStackNode *temp = s->top;
    tset val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

int isEmptyPStack(pstack *s)
{
    return s->top == NULL;
}

void destroyPStack(pstack *s)
{
    while (!isEmptyPStack(s))
    {
        popPStack(s);
    }
    free(s);
}

cstack *createCStack(void)
{
    cstack *s = (cstack *)malloc(sizeof(cstack));
    s->top = NULL;
    return s;
}

void pushCStack(cstack *s, char val)
{
    CStackNode *newNode = (CStackNode *)malloc(sizeof(CStackNode));
    newNode->data = val;
    newNode->next = s->top;
    s->top = newNode;
}

char popCStack(cstack *s)
{
    if (isEmptyCStack(s))
        return '\0';
    CStackNode *temp = s->top;
    char val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}

int isEmptyCStack(cstack *s)
{
    return s->top == NULL;
}

void destroyCStack(cstack *s)
{
    while (!isEmptyCStack(s))
    {
        popCStack(s);
    }
    free(s);
}