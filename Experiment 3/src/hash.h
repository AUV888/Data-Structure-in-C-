#ifndef HASH_H
#define HASH_H

#define TABLE_MAX_SIZE 0x80000

unsigned int hash_text(const char *str, unsigned int len);

typedef struct HASH_NODE
{
    char *text;
    struct HASH_NODE *next;
} node;

typedef struct HSET
{
    node *bucket[TABLE_MAX_SIZE];
    unsigned long size;
} hset;

hset *create_hset(void);

#endif