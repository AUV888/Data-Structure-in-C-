#include <stdlib.h>
#include "hash.h"

unsigned int hash_text(const char *str, unsigned int len)
{
    if (!str || len == 0)
        return 0;
    unsigned char group[4] = {0, 0, 0, 0};
    for (unsigned int i = 0; i < len; i++)
    {
        group[i % 4] ^= (unsigned char)str[i]; // use xor rather than +
    }
    for (unsigned int i = 0; i < 4; i++)
    {
        unsigned char b = group[i];
        b = (b >> 5) ^ (b & 0x1F); // compress 8 bit -> 5 bit
        group[i] = b;
    }
    unsigned int hash = 0;
    hash |= (group[0] << 15);
    hash |= (group[1] << 10);
    hash |= (group[2] << 5);
    hash |= (group[3] << 0); // make a 20 bit output hash value

    hash ^= (hash << 13);
    hash ^= (hash >> 17);
    hash ^= (hash << 5); // avalanche

    return hash % TABLE_MAX_SIZE;
}

hset *create_hset(void)
{
    hset *dest = (hset *)malloc(sizeof(hset));
    return dest;
}