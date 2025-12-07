#ifndef HASH_ADT_H
#define HASH_ADT_H

#include "hash.h"

int InitSet(hset *s);
int DestroySet(hset **s);
int SetInsert(hset *s, char *src);
int SetErase(hset *s, char *src);
int SetClear(hset *s);
int SetFind(hset *s, char *src);
unsigned long SetSize(hset *s);
/*shouldn't use hset s for arugment since it will copy entire structure
 *as argument thus causing segmentation fault!!!
 */

#endif