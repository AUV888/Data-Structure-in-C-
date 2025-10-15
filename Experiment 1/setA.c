#include <stdio.h>
#include <stdlib.h>
#define SIZE_OF_SET 65536 // must be multiples of 8
#define BYTE_OF_SET SIZE_OF_SET >> 3

static const char popcount_table[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

struct SET
{
    char *data;
    long len;
};
typedef struct SET set;
int InitSet(set *);
int DestroySet(set **);
int SetInsert(set *, int);
int SetErase(set *, int);
int SetClear(set *);
int SetFind(set *, int);
int SetSize(set);
int SetIntersection(set, set, set *);

int main()
{
    return 0;
}
int InitSet(set *s)
{
    if (s == NULL)
        return 0;
    s->data = (char *)malloc(BYTE_OF_SET * sizeof(char));
    if (s->data == NULL)
        return 0;
    s->len = 0;
    return 1;
}
int DestroySet(set **s)
{
    if ((*s) == NULL || (*s)->data == NULL)
        return 0;
    if ((*s)->data != NULL)
    {
        free((*s)->data);
        (*s)->data = NULL;
    }
    free(*s);
    *s = NULL;
    return 1;
}
int SetInsert(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = 0x80 >> col;
    s->len += !(s->data[row] & mask);
    s->data[row] |= mask;
    return 1;
}
int SetErase(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = ~(0x80 >> col);
    s->len -= !(s->data[row] & ~mask);
    s->data[row] &= mask;
    return 1;
}
int SetClear(set *s)
{
    if (s == NULL || s->data == NULL)
        return 0;
    for (int i = 0; i < BYTE_OF_SET; i++)
        s->data[i] = 0;
    s->len = 0;
    return 1;
}
int SetFind(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = 0x80 >> col;
    return !!(s->data[row] & mask);
}
int SetSize(set s)
{
    return s.len;
}
int SetIntersection(set sa, set sb, set *sc)
{
    for (int i = 0; i < BYTE_OF_SET; i++)
    {
        sc->data[i] = sa.data[i] & sb.data[i];
        sc->len += popcount_table[sc->data[i]];
    }
    return 1;
}