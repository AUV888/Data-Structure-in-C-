#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    RandomFind(a);
    RandomErase(a);
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
    FILE *fp = fopen("insert.in", "r");
    if (!fp)
    {
        fprintf(stderr, "cannot open insert.in\n");
        return;
    }
    int len, cnt = 0;
    while (fscanf(fp, "%d", &len) == 1)
    {
        if (cnt % 2000 == 0)
            printf("Inserting: %d / 500000\r", cnt);
        if (len == -1)
        {
            break;
        }
        char *word = (char *)malloc(len + 1);
        if (!word)
        {
            fprintf(stderr, "Memory allocation failed\n");
            break;
        }
        fscanf(fp, "%s", word);
        word[len] = '\0';
        SetInsert(s, word);
        cnt++;
    }
    printf("\n");
    fclose(fp);
    return;
}
void RandomFind(set *s)
{
    FILE *fp = fopen("find.in", "r");
    if (!fp)
    {
        fprintf(stderr, "cannot open find.in\n");
        return;
    }
    int len, cnt = 0, found = 0;
    while (fscanf(fp, "%d", &len) == 1)
    {
        if (cnt % 2000 == 0)
            printf("Finding: %d / 100000\r", cnt);
        if (len == -1)
        {
            break;
        }
        char *word = (char *)malloc(len + 1);
        if (!word)
        {
            fprintf(stderr, "Memory allocation failed\n");
            break;
        }
        fscanf(fp, "%s", word);
        word[len] = '\0';
        if(SetFind(s,word))
            found++;
        
        cnt++;
    }
    printf("\nFound: %d / 100000\n");
    fclose(fp);
    return;
}
void RandomErase(set *s)
{
    FILE *fp = fopen("erase.in", "r");
    if (!fp)
    {
        fprintf(stderr, "cannot open erase.in\n");
        return;
    }
    int len, cnt = 0, erased = 0;
    while (fscanf(fp, "%d", &len) == 1)
    {
        if (cnt % 2000 == 0)
            printf("Erasing: %d / 500000\r", cnt);
        if (len == -1)
        {
            break;
        }
        char *word = (char *)malloc(len + 1);
        if (!word)
        {
            fprintf(stderr, "Memory allocation failed\n");
            break;
        }
        fscanf(fp, "%s", word);
        word[len] = '\0';
        if (SetErase(s, word))
            erased++;
        cnt++;
    }
    printf("\nErased: %d / 500000\n", erased);
    fclose(fp);
    return;
}