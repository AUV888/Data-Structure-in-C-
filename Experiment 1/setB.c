#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    char *text;
    long string_len;
    struct NODE *next;
};
typedef struct NODE node;

struct SET
{
    long len;
    node *head;
};
typedef struct SET set;

int InitSet(set **);
int DestroySet(set **);
int SetInsert(set *, char *);
int SetErase(set *, char *);
int SetClear(set *);
int SetFind(set *, char *);
int SetSize(set, char *);
int SetUnion(set *, set *, set *);
void RandomInsert(set *);
void RandomFind(set *);
void RandomErase(set *);

int main()
{
    set *a, *b, *c;
    InitSet(&a);
    InitSet(&b);
    InitSet(&c);
    RandomInsert(a);
    RandomErase(a);
    RandomFind(a);
    DestroySet(&a);
    DestroySet(&b);
    DestroySet(&c);
    return 0;
}
int InitSet(set **s)
{
}
int DestroySet(set **s)
{
}
int SetInsert(set *s, char *t)
{
}
int SetErase(set *s, char *t)
{
}
int SetClear(set *s)
{
}
int SetFind(set *s, char *t)
{
}
int SetSize(set s, char *t)
{
}
int SetUnion(set *sa, set *sb, set *sc)
{
}
void RandomInsert(set *s)
{
    return;
}
void RandomFind(set *s)
{
    return;
}
void RandomErase(set *s)
{
    return;
}