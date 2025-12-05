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
        }//
        father = cur;
    }
    return 1;
}
// ...existing code...
int tSetErase(tset *s, char *src)
{
    if (!s || !(*s) || !src)
        return 0;
    size_t slen = strlen(src);
    if (slen == 0)
        return 0;

    /* 分配记录数组：每层的 head 指针、前驱兄弟和匹配节点 */
    tset *layer_head_ptr = (tset *)malloc(sizeof(tset) * slen); // 存放指向该层头节点的指针地址（实际类型 tset*）
    tset *prev_sib = (tset *)malloc(sizeof(tset) * slen);
    tset *cur_node = (tset *)malloc(sizeof(tset) * slen);
    if (!layer_head_ptr || !prev_sib || !cur_node)
    {
        free(layer_head_ptr);
        free(prev_sib);
        free(cur_node);
        return 0;
    }

    tset parent = NULL;
    tset layer_head = *s;
    size_t idx = 0;
    for (long long i = (long long)slen - 1; i >= 0; --i)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch; // lowercase

        tset prev = NULL;
        tset cur = layer_head;
        while (cur && cur->d != ch)
        {
            prev = cur;
            cur = cur->sib;
        }
        if (!cur)
        {
            /* 单词不存在，释放临时数组并返回 0 */
            free(layer_head_ptr);
            free(prev_sib);
            free(cur_node);
            return 0;
        }

        /* 记录本层信息 */
        if (parent == NULL)
            layer_head_ptr[idx] = (tset *)s; /* 根层头的地址 */
        else
            layer_head_ptr[idx] = &parent->next; /* 父节点的 next 指针地址即本层头 */

        prev_sib[idx] = prev;
        cur_node[idx] = cur;

        /* 进入下一层 */
        parent = cur;
        layer_head = cur->next;
        idx++;
    }

    /* 从最深层（idx-1）向上回溯并删除可以释放的节点 */
    for (long j = (long)idx - 1; j >= 0; --j)
    {
        tset node = cur_node[j];
        /* 只有当 node->next == NULL 时可删除（表示没有更深的子节点） */
        if (node->next != NULL)
            break;

        /* 从兄弟链中断开 node */
        if (prev_sib[j] == NULL)
        {
            /* node 是该层的头节点，更新头指针（layer_head_ptr[j] 指向该层的头） */
            *(layer_head_ptr[j]) = node->sib;
        }
        else
        {
            prev_sib[j]->sib = node->sib;
        }

        /* free 节点 */
        free(node);
        /* 注意：父层对应的 next 指针已通过上面操作被更新为 node->sib（可能为 NULL 或其他兄弟） */
    }

    free(layer_head_ptr);
    free(prev_sib);
    free(cur_node);
    return 1;
}
// ...existing code...
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
// ...existing code...
int tSetFind(tset *s, char *src)
{
    if (!s || !(*s) || !src)
        return 0;
    size_t slen = strlen(src);
    if (slen == 0)
        return 0;

    tset parent = NULL;
    for (long long i = (long long)slen - 1; i >= 0; --i)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch; // lowercase

        tset cur = (parent == NULL ? *s : parent->next);
        while (cur && cur->d != ch)
            cur = cur->sib;
        if (!cur)
            return 0; // 未找到该字符，字符串不存在
        parent = cur;
    }
    return 1; // 找到完整路径，字符串存在
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
