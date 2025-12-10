#ifndef STACKQUEUE_H
#define STACKQUEUE_H
#include "trie.h"
#include "trie_adt.h"
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

typedef struct PStackNode
{
    tset data;
    struct PStackNode *next;
} PStackNode;

typedef struct POINTERSTACK
{
    PStackNode *top;
} pstack;

typedef struct CStackNode
{
    char data;
    struct CStackNode *next;
} CStackNode;

typedef struct CHARSTACK
{
    CStackNode *top;
} cstack;

pstack *createPStack(void);
void pushPStack(pstack *s, tset val);
tset popPStack(pstack *s);
int isEmptyPStack(pstack *s);
void destroyPStack(pstack *s);


cstack *createCStack(void);
void pushCStack(cstack *s, char val);
char popCStack(cstack *s);
int isEmptyCStack(cstack *s);
void destroyCStack(cstack *s);

Queue *createQueue(void);
int isEmpty(Queue *q);
void enqueue(Queue *q, tset val);
tset dequeue(Queue *q);
void destroyQueue(Queue *q);
#endif