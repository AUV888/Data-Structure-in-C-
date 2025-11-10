#include <stdio.h>

void get_next(char T[], int *next)
{
    int i = 1;
    next[1] = 0;
    int j = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

void get_nextval(char T[], int *nextval)
{
    int i = 1;
    nextval[1] = 0;
    int j = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            if (T[i] != T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

void plist(int *a)
{
    int l = a[0];
    for (int i = 1; i <= l; i++)
        printf("%d ", a[i]);
    printf("\n");
}
#define LEN 10
int main()
{

    char t2[] = {4, 'a', 'a', 'a', 'b'};
    int nx2[4 + 1], nv2[4 + 1];
    nx2[0] = 4;
    nv2[0] = 4;
    get_next(t2, &nx2[0]);
    get_nextval(t2, &nv2[0]);
    plist(nx2);
    plist(nv2);

    char t[] = {7, 'a', 'b', 'c', 'a', 'b', 'a', 'a'};
    int nx[7 + 1], nv[7 + 1];
    nx[0] = 7;
    nv[0] = 7;
    get_next(t, &nx[0]);
    get_nextval(t, &nv[0]);
    plist(nx);
    plist(nv);

    char t1[] = {10, 'a', 'd', 'a', 'b', 'b', 'a', 'd', 'a', 'd', 'a'};
    int nx1[10 + 1], nv1[10 + 1];
    nx1[0] = 10;
    nv1[0] = 10;
    get_next(t1, &nx1[0]);
    get_nextval(t1, &nv1[0]);
    plist(nx1);
    plist(nv1);

    return 0;
}