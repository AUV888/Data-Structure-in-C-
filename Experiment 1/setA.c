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
int DestroySet(set **);
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
    if (s == NULL)
        return 0;
    s->data = (char *)malloc(8192 * sizeof(char));
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
    (*s)->len = 0;
    return 1;
}
int SetInsert(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = 0x80 >> col;
    s->data[row] |= mask;
    s->len++;
    return 1;
}
int SetErase(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (val >> 3) << 3;
    char mask = ~(0x80 >> col);
    s->data[row] &= mask;
    s->len--;
    return 1;
}
int SetClear(set *s)
{
    if (s == NULL || s->data == NULL)
        return 0;
    for (int i = 0; i < 8192; i++)
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
    if (!!(s->data[row] & mask))
        return 1;
    else
        return 0;
}
int SetSize(set s, int val)
{
    return  s.len;
}
int SetIntersection(set sa, set sb, set *sc)
{
    for(int i = 0; i < 8192; i++){
        sc->data[i] = sa.data[i] & sb.data[i];
        
    return 1;
}