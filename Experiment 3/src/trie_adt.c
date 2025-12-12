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
    int diff = 0;
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch; // lowercase
    L1:
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
            diff++;
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
        if (i == 0)
        {
            i--;
            ch = '\0';
            goto L1;
        }
    }
    return !!diff;
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
    int searchlen = 1;
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch;
    L2:
        while (cur->sib)
        {
            if (cur->d == ch)
                break;
            cur = cur->sib;
            searchlen++;
        }
        if (cur->d != ch)
            return 0;
        else
        {
            cur = cur->next;
            searchlen++;
        }
        if (i == 0)
        {
            i--;
            ch = '\0';
            goto L2;
        }
    }
    return searchlen;
}
unsigned long tSetSize(tset s)
{
    if (!s)
        return 0;
    unsigned long cnt = 0;
    Queue *q = createQueue();
    enqueue(q, s);

    while (!isEmpty(q))
    {
        tset head = q->front->data;
        if (head->sib)
            enqueue(q, head->sib);
        if (head->next)
            enqueue(q, head->next);
        if (head->next == NULL) // this is the end of a string
            cnt++;
        dequeue(q);
    }
    destroyQueue(q);
    return cnt;
}