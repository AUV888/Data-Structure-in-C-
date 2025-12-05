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
        return NULL;
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
    *s = NULL;
    return 1;
}
int tSetInsert(tset *s, char *src)
{
    if (!s || !src)
        return 0;
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
        }//
        father = cur;
    }
    return 1;
}
int tSetErase(tset *s, char *src)
{
    if (!(*s) || !src)
        return 0;
    size_t slen = strlen(src);
    tset cur = *s;
    Queue *q = createQueue();
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch;
        while (cur->sib)
        {
            if (cur->d == ch)
                break;
            cur = cur->sib;
        }
        int notSharedNode = cur->sib == NULL;
        if (cur->d != ch)
            return 0;
        tset tmp = cur;
        cur = cur->next;
        if (notSharedNode)
            enqueue(q, tmp);
        else
        {
            while (!isEmpty(q))
                dequeue(q);
        }
    }
    while (!isEmpty(q))
    {
        tset tmp = dequeue(q);
        if (tmp == *s)
            *s = NULL;
        free(tmp);
    }
    return 1;
}
/*
int tSetClear(tset s)
{
    while(s)
    {
        tset next_layer = s->next;
        tset sib = s->sib;
        free(s);
        s = sib;
        if (!s)
            s = next_layer;
    }
    return 1;
}
*/
int tSetFind(tset s, char *src)
{
    if (!s || !src)
        return 0;
    size_t slen = strlen(src);
    tset cur = s;
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch;
        while (cur->sib)
        {
            if (cur->d == ch)
                break;
            cur = cur->sib;
        }
        if (cur->d != ch)
            return 0;
        else
            cur = cur->next;
    }
    return 1;
}
unsigned long tSetSize(tset s)
{
    if (!s)
        return 0ULL;

    unsigned long count = 0;
    Queue *q = createQueue();
    enqueue(q, s);

    while (!isEmpty(q))
    {
        tset node = dequeue(q);
        if (!node)
            continue;
        // 约定：没有更深一层（next == NULL）的节点视作一个完整的元素（与 tSetErase 的回溯删除策略一致）
        if (node->next == NULL)
            ++count;

        if (node->sib)
            enqueue(q, node->sib);
        if (node->next)
            enqueue(q, node->next);
    }

    destroyQueue(q);
    return count;
}
// ...existing code...
