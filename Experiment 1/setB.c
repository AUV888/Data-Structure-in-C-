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
    *s = (set *)malloc(sizeof(set));
    if (!*s)
    {
        return 0;
    }
    (*s)->len = 0;
    (*s)->head = NULL;
    return 1;
}
int DestroySet(set **s)
{
    if (!s || !*s)
        return 0;
        node *current = (*s)->head;
        node *next_node;
        while (current != NULL)
        {
            next_node = current->next;
            free(current->text);
            free(current);
            current = next_node;
        }
    *s = NULL;
    return 1;
}
int SetInsert(set *s, char *t)
{
    if (!s || !t)
        return 0;
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
        return 0;
    new_node->string_len = strlen(t);
    new_node->text = (char *)malloc(new_node->string_len + 1);
    if (!new_node->text)
    {
        free(new_node);
        return 0;
    }
    strcpy(new_node->text, t);
    new_node->next = s->head;
    s->head = new_node;
    s->len++;
    return 1;
}
int SetErase(set *s, char *t)
{
    if (!s || !t || !s->head)
        return 0;
    node *current = s->head;
    node *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->text, t) == 0)
        {
            if (previous == NULL)
            {
                s->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current->text);
            free(current);
            s->len--;
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}
int SetClear(set *s)
{
    if(!s)
        return 0;
    node* current = s->head;
    node* next_node;
    while(current != NULL)
    {
        next_node = current->next;
        free(current->text);
        free(current);
        current = next_node;
    }
    s->head = NULL;
    s->len = 0;
    return 1;
}
int SetFind(set *s, char *t)
{
    if (!s || !t)
        return 0;
    node *current = s->head;
    while (current != NULL)
    {
        if (strcmp(current->text, t) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
int SetSize(set s)
{
   return s.len;
}
int SetUnion(set *sa, set *sb, set *sc)
{
    if (!sa || !sb || !sc)
        return 0;
    node *current = sa->head;
    while (current != NULL)
    {
        SetInsert(sc, current->text);
        current = current->next;
    }
    current = sb->head;
    while (current != NULL)
    {
        if (!SetFind(sc, current->text))
        {
            SetInsert(sc, current->text);
        }
        current = current->next;
    }
    return 1;
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