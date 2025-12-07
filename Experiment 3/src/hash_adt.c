#include "hash.h"
#include "hash_adt.h"
#include <string.h>
#include <stdlib.h>

int InitSet(hset *s)
{
    if (!s)
        return 0;
    memset(s->bucket, NULL, sizeof(s->bucket));
    s->size = 0;
    return 1;
}
int DestroySet(hset **s)
{
    if (!s || !(*s))
        return 0;
    for (int i = 0; i < TABLE_MAX_SIZE; i++)
    {
        node *cur = (*s)->bucket[i];
        while (cur)
        {
            node *tmp = cur->next;
            free(cur->text);
            free(cur);
            cur = tmp;
        }
    }
    (*s)->size = 0;
    free(*s);
    *s = NULL;
    return 1;
}
int SetInsert(hset *s, char *src)
{
    if (!s || !src)
        return 0;

    unsigned long hash = hash_text(src, strlen(src));
    node *cur = s->bucket[hash];
    
    while (cur)
    {
        if (strcmp(cur->text, src) == 0)
            return 0; // 已存在
        cur = cur->next;
    }

    node *n = (node *)malloc(sizeof(node));
    if (!n)
        return 0;
    
    n->text = (char *)malloc(strlen(src) + 1);
    if (!n->text)
    {
        free(n);
        return 0;
    }
    
    strcpy(n->text, src);
    n->next = s->bucket[hash];
    s->bucket[hash] = n;
    s->size++;
    return 1;
}

int SetErase(hset *s, char *src)
{
    if (!s || !src)
        return 0;

    unsigned long hash = hash_text(src, strlen(src));
    node *cur = s->bucket[hash];
    node *prev = NULL;

    while (cur)
    {
        if (strcmp(cur->text, src) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                s->bucket[hash] = cur->next;

            free(cur->text);
            free(cur);
            s->size--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0; // 未找到
}

int SetClear(hset *s)
{
    if (!s)
        return 0;

    for (int i = 0; i < TABLE_MAX_SIZE; i++)
    {
        node *cur = s->bucket[i];
        while (cur)
        {
            node *tmp = cur->next;
            free(cur->text);
            free(cur);
            cur = tmp;
        }
        s->bucket[i] = NULL;
    }
    s->size = 0;
    return 1;
}

int SetFind(hset *s, char *src)
{
    if (!s || !src)
        return 0;
    unsigned long hash = hash_text(src, strlen(src));
    node *cur = s->bucket[hash];
    
    while (cur)
    {
        if (strcmp(cur->text, src) == 0)
            return 1;
        cur = cur->next;
    }
    return 0;
}

unsigned long SetSize(hset s)
{
    return s.size;
}