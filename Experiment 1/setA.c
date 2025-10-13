#include <stdio.h>
#include <stdlib.h>
#define SIZE_OF_SET 65536

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
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = 0x80 >> col;
    s->data[row] |= mask;
    return 1;
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
int SetIntersection(set sa, set sb, set *sc)
{
}