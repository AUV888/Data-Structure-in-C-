#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKET_CNT (1u << 20)

struct NODE
{
    char *text;
    long string_len;
    struct NODE *prev;
    struct NODE *next;
    struct NODE *hash_next;
};
typedef struct NODE node;

struct SET
{
    long len;
    node *head;
};
typedef struct SET set;

static node *bucket[BUCKET_CNT];

int InitSet(set **);
int DestroySet(set **);
int SetInsert(set *, char *);
int SetErase(set *, char *);
int SetClear(set *);
int SetFind(set *, char *);
int SetSize(set);
int SetUnion(set *, set *, set *);
void RandomInsert(set *);
void RandomFind(set *);
void RandomErase(set *);
static inline unsigned int hash_text(const char *, size_t);
static void link_node(set *, node *, unsigned int);

int main()
{
    set *a;
    InitSet(&a);
    RandomInsert(a);
    RandomFind(a);
    RandomErase(a);
    DestroySet(&a);
    return 0;
}
int InitSet(set **s)
{
    *s = (set *)malloc(sizeof(set));
    if (!*s)
        return 0;
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
    memset(bucket, NULL, sizeof(bucket));
    *s = NULL;
    return 1;
}
int SetInsert(set *s, char *t)
{
    if (!s || !t)
        return 0;

    size_t tlen = strlen(t);
    unsigned int h = hash_text(t, tlen);
    for (node *p = bucket[h]; p; p = p->hash_next)
        if (p->string_len == tlen && memcmp(p->text, t, tlen) == 0)
            return 1;

    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
        return 0;
    new_node->string_len = tlen;
    new_node->text = (char *)malloc(new_node->string_len + 1);
    new_node->prev = NULL;
    if (!new_node->text)
    {
        free(new_node);
        return 0;
    }
    strcpy(new_node->text, t);
    link_node(s, new_node, h);
    return 1;
}
int SetErase(set *s, char *t)
{
    if (!s || !t || !s->head)
        return 0;
    size_t tlen = strlen(t);
    unsigned int h = hash_text(t, tlen);
    node *prev = NULL;
    for (node *p = bucket[h]; p; prev = p, p = p->hash_next)
    {
        if (p->string_len == tlen && memcmp(p->text, t, tlen) == 0)
        {
            // remove from hash
            if (prev == NULL)
                bucket[h] = p->hash_next;
            else
                prev->hash_next = p->hash_next;
            // remove from main linklist
            if (p->prev)
                p->prev->next = p->next;
            else
                s->head = p->next;
            if (p->next)
                p->next->prev = p->prev;
            free(p->text);
            free(p);
            s->len--;
            return 1;
        }
    }
    return 0;
}
int SetClear(set *s)
{
    if (!s)
        return 0;
    node *current = s->head;
    node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current->text);
        free(current);
        current = next_node;
    }
    memset(bucket, NULL, sizeof(bucket));
    s->head = NULL;
    s->len = 0;
    return 1;
}
int SetFind(set *s, char *t)
{
    if (!s || !t)
        return 0;
    node *current = s->head;
    long dest_len = strlen(t);
    unsigned int h = hash_text(t, dest_len);
    for (node *p = bucket[h]; p; p = p->hash_next)
        if (p->string_len == dest_len && memcmp(p->text, t, dest_len) == 0)
            return 1;
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
        if (cnt % 1000 == 0)
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
        if (SetFind(s, word))
            found++;

        cnt++;
    }
    printf("\nFound: %d / 100000\n", found);
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
        if (cnt % 1000 == 0)
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
static inline unsigned int hash_text(const char *s, size_t len)
{
    unsigned int h = 0x811c9dc5u;
    for (size_t i = 0; i < len; ++i)
    {
        h ^= (char)s[i];
        h *= 0x01000193u;
    }
    return h & (BUCKET_CNT - 1);
}
static void link_node(set *s, node *p, unsigned int hash)
{
    p->next = s->head;
    if (p->next)
        p->next->prev = p;
    p->prev = NULL;
    s->head = p;
    p->hash_next = bucket[hash];
    bucket[hash] = p;
    s->len++;
}