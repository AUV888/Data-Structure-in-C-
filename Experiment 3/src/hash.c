#include <stdlib.h>
#include "hash.h"

unsigned int hash_text(const char *str, unsigned int len)
{
}

hset *create_hset(void)
{
    hset *dest = (hset *)malloc(sizeof(hset));
    return dest;
}