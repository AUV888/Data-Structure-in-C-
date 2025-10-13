#include <stdio.h>
#include <stdlib.h>

struct SET
{
    char *data;
    long len;
};
typedef struct SET set;
int InitSet(set *);
int DestroySet(set *);
int SetInsert(set *, int);
int SetErase(set *, int);
int SetClear(set *);
int SetFind(set *, int);
int SetSize(set, int);
int SetUnion(set, set, set *);

int main()
{
    return 0;
}
int InitSet(set *s)
{
}
int DestroySet(set *s)
{
}
int SetInsert(set *s, int val)
{
}
int SetErase(set *s, int val)
{
}
int SetClear(set *s)
{
}
int SetFind(set *s, int val)
{
}
int SetSize(set s, int val)
{
}
int SetUnion(set sa, set sb, set *sc)
{
}