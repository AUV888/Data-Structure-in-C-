#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define initial_vol 5
typedef struct SET set;
typedef int elem;

struct SET
{
    int len;
    int vol;
    elem *data;
};
int InitSet(set *s);
int DestroySet(set *s);
int SetInsert(set *s, elem val);
int SetErase(set *s, elem val);
int SetClear(set *s);
int SetFind(set s, elem val);
int SetSize(set s);
int SetUnion(set sa, set sb, set *sc);
int SetIntersection(set sa, set sb, set *sc);
void TestFunctions(void);   // For testing the program only
void DebugPrintSet(set *s); // For debug use only

int main()
{
    TestFunctions();
    return 0;
}

int InitSet(set *s)
{
    if (s == NULL)
        return 0;
    s->data = (elem *)malloc(initial_vol * sizeof(elem));
    if (s->data == NULL)
        return 0;
    s->len = 0;
    s->vol = initial_vol;
    return 1;
}

int DestroySet(set *s)
{
    if (s == NULL || s->data == NULL)
        return 0;
    free(s->data);
    s->len = 0;
    s->vol = 0;
    return 1;
}

int SetInsert(set *s, elem val)
{
    if (s == NULL || s->data == NULL)
        return 0;
    if (SetFind(*s, val))
        return 1;
    if (s->len == s->vol)
    {
        int prev_vol = s->vol;
        elem *new_data = (elem *)malloc((prev_vol + initial_vol) * sizeof(elem));
        if (new_data == NULL)
            return 0;
        memcpy(new_data, s->data, prev_vol * sizeof(elem));
        free(s->data);
        s->data = new_data;
        s->vol += initial_vol;
    }
    s->data[s->len] = val;
    s->len++;
    return 1;
}

int SetErase(set *s, elem val)
{
    if (s == NULL || s->data == NULL || !SetFind(*s, val))
        return 0;
    int pos = -1;
    for (int i = 0; i < s->len; i++)
    {
        if (s->data[i] == val)
        {
            pos = i;
            break;
        }
    }
    for (int i = pos; i < s->len - 1; i++)
        s->data[i] = s->data[i + 1];
    s->len--;
    return 1;
}

int SetClear(set *s)
{
    if (s == NULL || s->data == NULL)
        return 0;
    s->len = 0;
    return 1;
}

int SetFind(set s, elem val)
{
    if (s.data == NULL)
        return 0;
    for (int i = 0; i < s.len; i++)
    {
        if (s.data[i] == val)
            return 1;
    }
    return 0;
}

int SetSize(set s)
{
    if (s.data == NULL)
        return 0;
    return s.len;
}

int SetUnion(set sa, set sb, set *sc)
{
    if (sc == NULL || sc->data == NULL || sa.data == NULL || sb.data == NULL)
        return 0;
    if (sc->data)
        free(sc->data);
    sc->data = (elem *)malloc((sa.len + sb.len) * sizeof(elem));
    if (sc->data == NULL)
        return 0;
    sc->vol = sa.len + sb.len;
    memcpy(sc->data, sa.data, sa.len * sizeof(elem));
    sc->len = sa.len;
    int top = sa.len;
    for (int i = 0; i < sb.len; i++)
    {
        if (!SetFind(*sc, sb.data[i]))
        {
            sc->data[top] = sb.data[i];
            sc->len++;
            top++;
        }
    }
    return 1;
}

int SetIntersection(set sa, set sb, set *sc)
{
    if (sc == NULL || sc->data == NULL || sa.data == NULL || sb.data == NULL)
        return 0;
    if (sc->data)
        free(sc->data);
    int minimum_vol = sa.len > sb.len ? sb.len : sa.len;
    sc->data = (elem *)malloc(minimum_vol * sizeof(elem));
    sc->len = 0;
    if (sc->data == NULL)
        return 0;
    for (int i = 0; i < sb.len; i++)
    {
        if (SetFind(sa, sb.data[i]))
        {
            sc->data[sc->len] = sb.data[i];
            sc->len++;
        }
    }
    return 1;
}

void TestFunctions(void) // For testing the program only
{
    int a[] = {3, 5, 6, 7, 7, 6, 2}, b[] = {1, 4, 5, 6, 9, -11, 13, 19};
    set sa, sb, sc;
    InitSet(&sa);
    InitSet(&sb);
    InitSet(&sc);
    printf("test initialize:\n");
    DebugPrintSet(&sa);
    DebugPrintSet(&sb);
    DebugPrintSet(&sc);
    for (int i = 0; i < 7; i++)
        SetInsert(&sa, a[i]);
    for (int i = 0; i < 8; i++)
        SetInsert(&sb, b[i]);

    printf("\ntest if A and B are inserted correctly:\n");
    DebugPrintSet(&sa);
    DebugPrintSet(&sb);
    printf("\ntest erase function:\n");
    SetErase(&sa, 12);
    SetErase(&sa, 6);
    DebugPrintSet(&sa);
    printf("\ntest find function in A:\n");
    printf("find 6: %d\tfind 15: %d\n", SetFind(sa, 6), SetFind(sa, 15));
    printf("\ntest size function:\nA size: %d\tB size:%d\n", SetSize(sa), SetSize(sb));
    printf("\ntest intersection:\n");
    SetIntersection(sa, sb, &sc);
    DebugPrintSet(&sc);
    printf("\ntest union:\n");
    SetUnion(sa, sb, &sc);
    DebugPrintSet(&sc);
    printf("\ntest clear:\n");
    SetClear(&sc);
    DebugPrintSet(&sc);
    printf("\ntest destroy:\n");
    DestroySet(&sa);
    DestroySet(&sb);
    DestroySet(&sc);
    DebugPrintSet(&sa);
    DebugPrintSet(&sb);
    DebugPrintSet(&sc);
    return;
}

void DebugPrintSet(set *s) // For debug use only
{
    if (s == NULL)
    {
        fprintf(stderr, "No Such Set\n");
        return;
    }
    if (s->data == NULL)
    {
        fprintf(stderr, "Data in Set Not Available\n");
        return;
    }
    if (s->vol < s->len || s->vol == 0)
    {
        fprintf(stderr, "The Set Has No Volume\n");
        return;
    }
    if (s->len == 0 && s->vol >= 0)
    {
        printf("Empty Set\n");
        return;
    }
    for (int i = 0; i < s->len; i++)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
    return;
}