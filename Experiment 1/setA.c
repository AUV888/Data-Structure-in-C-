#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_OF_SET 65536 // must be multiples of 8
#define BYTE_OF_SET SIZE_OF_SET >> 3

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
void TestFunctions(void);
void PrintSet(set *s);

int main()
{
    TestFunctions();
    return 0;
}
int InitSet(set *s)
{
    if (s == NULL)
        return 0;
    s->data = (char *)malloc(BYTE_OF_SET * sizeof(char));
    if (s->data == NULL)
        return 0;
    memset(s->data, 0, BYTE_OF_SET);
    s->len = 0;
    return 1;
}
int DestroySet(set **s)
{
    if ((*s) == NULL || (*s)->data == NULL)
        return 0;
    free((*s)->data);
    (*s)->data = NULL;
    free(*s);
    *s = NULL;
    return 1;
}
int SetInsert(set *s, int val)
{
    if (s == NULL || s->data == NULL || val >= SIZE_OF_SET)
        return 0;
    int row = val >> 3;
    int col = val - (row << 3);
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
    int col = val - (row << 3);
    char mask = ~(0x80 >> col);
    s->len -= !!(s->data[row] & ~mask);
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
    int col = val - (row << 3);
    char mask = 0x80 >> col;
    return !!(s->data[row] & mask);
}
int SetSize(set s)
{
    return s.len;
}
int SetIntersection(set sa, set sb, set *sc)
{
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
    for (int i = 0; i < BYTE_OF_SET; i++)
    {
        sc->data[i] = sa.data[i] & sb.data[i];
        sc->len += popcount_table[sc->data[i]];
    }
    return 1;
}
void TestFunctions(void)
{
    set *a, *b, *c;
    a = (set *)malloc(sizeof(set));
    b = (set *)malloc(sizeof(set));
    c = (set *)malloc(sizeof(set));
    printf("Init Set a,b,c: %d %d %d\n", InitSet(a), InitSet(b), InitSet(c));
    SetInsert(a, 3);
    SetInsert(a, 2147);
    SetInsert(a, 65535);
    printf("a is: ");
    PrintSet(a);
    SetErase(a, 2147);
    SetErase(a, 5555);
    printf("After erase, a is: ");
    PrintSet(a);
    printf("a length is: %d\n", SetSize(*a));
    SetInsert(b, 5);
    SetInsert(b, 9876);
    SetInsert(b, 65535);
    SetInsert(b, 1234);
    printf("b is: ");
    PrintSet(b);
    SetIntersection(*a, *b, c);
    printf("c is: ");
    PrintSet(c);
    printf("c length is: %d\n", SetSize(*c));
    SetClear(a);
    printf("after clear, a is: ");
    PrintSet(a);
    DestroySet(&a);
    printf("after destory, a is: ");
    PrintSet(a);
    DestroySet(&b);
    DestroySet(&c);
}
void PrintSet(set *s)
{
    if (!s)
    {
        printf("no such set\n");
        return;
    }
    int flag = 0;
    for (int i = 0; i < 65536; i++)
    {
        if (SetFind(s, i))
        {
            printf("%d ", i);
            flag++;
        }
    }
    if (!flag)
        printf("empty");
    printf("\n");
    return;
}