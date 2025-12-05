#include "trie_adt.h"
#include <stdlib.h>
#include <string.h>
/*
int InitSet(tset s)
{
}
*/

typedef struct QueueNode
{
    tset data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

static Queue *createQueue(void)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

static int isEmpty(Queue *q)
{
    return q->front == NULL;
}
static void enqueue(Queue *q, tset val)
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

static tset dequeue(Queue *q)
{
    if (isEmpty(q))
        return NULL; // 错误值，表示队列空
    QueueNode *temp = q->front;
    tset val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return val;
}

static void destroyQueue(Queue *q)
{
    while (!isEmpty(q))
    {
        dequeue(q);
    }
    free(q);
}

int tDestroySet(tset *s) // have problems, but ignore it first
{
    if (!(*s))
        return 0;
    Queue *q = createQueue();
    enqueue(q, *s);
    while (!isEmpty(q))
    {
        tset tmp = q->front->data;
        if (!tmp)
            return 0;
        if (tmp->sib != NULL)
            enqueue(q, tmp->sib);
        if (tmp->next != NULL)
            enqueue(q, tmp->next);
        tmp = dequeue(q);
        free(tmp);
    }
    destroyQueue(q);
    return 1;
}
int tSetInsert(tset *s, char *src)
{
    size_t slen = strlen(src);
    tset father = NULL;
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch;    // lowercase
        tset cur = (father == NULL ? *s : father->next); // cur is in this layer
        char flag = (cur == NULL);                       // this layer has nothing?
        while (!flag && cur->sib)                        // find char in all siblings
        {
            if (cur->d == ch)
                break;
            cur = cur->sib;
        }

        if (flag || cur->d != ch) // haven't matched char or don't even have siblings
        {
            tset newNode = (tset)malloc(sizeof(tnode));
            if (!newNode)
                return 0;
            newNode->d = ch;
            newNode->sib = NULL;
            newNode->next = NULL;
            if (!flag) // no siblings matched
            {
                cur->sib = newNode;
                cur = newNode;
            }
            else // don't even have siblings in this layer
            {
                cur = newNode;
                if (father == NULL) // initial s
                    *s = cur;
                else
                    father->next = cur;
            }
        }
        father = cur;
    }
    return 1;
}
int tSetErase(tset s, char *src)
{
    return 1;
}
int tSetClear(tset s)
{
    return 1;
}
int tSetFind(tset s)
{
    return 1;
}
unsigned long tSetSize(tset s)
{
    return 1ULL;
}
