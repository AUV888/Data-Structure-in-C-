#include "trie_adt.h"
#include <stdlib.h>
#include <string.h>
#include "stackqueue.h"
#define DIRECT_POINTER -1
#define RIP 1
/*
int InitSet(tset s)
{
}
*/

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
        }
        if (cur->d != ch)
            return 0;
        else
            cur = cur->next;
        if (i == 0)
        {
            i--;
            ch = '\0';
            goto L2;
        }
    }
    return 1;
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

void tSetWildCardFind(tset s, char *src, char **res, int *retsize) // VERY BUGGY! DON'T EVEN TRY TO RUN!!!
{
    if (!s || !src || !res || !retsize)
        return;
    size_t slen = strlen(src);
    tset cur = s;
    cstack *cst = createCStack();
    // char come_from = DIRECT_POINTER;
    for (long long i = slen - 1; i >= 0; i--)
    {
        char ch = src[i];
        ch = ('A' <= ch && ch <= 'Z') ? ch + 32 : ch;
        if (ch == '*')
        {
            FoundWildcard(cur, res, retsize);
            return;
        }

    L2:
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
        if (i == 0)
        {
            i--;
            ch = '\0';
            goto L2;
        }
        else
            pushCStack(cst, ch);
    }
}
static void FoundWildcard(tset start, char **res, int *retsize)
{
    pstack *rip = createPStack();
    cstack *c = createCStack();
    char ComeFrom = DIRECT_POINTER;
    tset cur = start;
    pushPStack(rip, cur);
    while (!isEmptyPStack(rip))
    {
        if (ComeFrom == DIRECT_POINTER)
        {
            pushCStack(c, cur->d);
            pushPStack(rip, cur);
            if (cur->next)       // have child
                cur = cur->next; // go to explore child
            else                 // no child
            {
                // copy all chars in cstack to res
                // and self-add retsize
                int len = 0;
                CStackNode *temp = c->top;
                while (temp)
                {
                    len++;
                    temp = temp->next;
                }
                temp = c->top;
                char *str = (char *)malloc(len + 1);
                int i = 0;
                for (i = 0; i < len; i++)
                    str[i] = temp->data;
                str[i] = '\0';
                res[*retsize] = str;
                (*retsize)++;
                ComeFrom = RIP;
                popCStack(c);         // pop out current char
                cur = popPStack(rip); // go to father
            }
        }
        else // come from poping stack
        {
            if (cur->sib) // have siblings
            {
                pushPStack(rip, cur);
                ComeFrom = DIRECT_POINTER;
                cur = cur->sib;
            }
            else // nothing to do in this layer
            {
                popCStack(c);
                cur = popPStack(rip);
            }
        }
    }
}