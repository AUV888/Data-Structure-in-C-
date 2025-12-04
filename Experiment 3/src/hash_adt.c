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
}
int SetErase(hset *s, char *src)
{
}
int SetClear(hset *s)
{
}
int SetFind(hset *s)
{
}
unsigned long SetSize(hset s)
{
    return s.size;
}