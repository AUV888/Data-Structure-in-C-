#ifndef HASH_H
#define HASH_H

#define TABLE_MAX_SIZE 0x40000

inline unsigned int hash_text(const char *str, unsigned int len);

typedef struct HASH_NODE
{
    char *text;
    struct HASH_NODE *next;
} node;



#endif