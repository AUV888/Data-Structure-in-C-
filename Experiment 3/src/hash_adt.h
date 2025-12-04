#ifndef HASH_ADT_H
#define HASH_ADT_H

#include "hash.h"

int InitSet(hset *s);
int DestroySet(hset **s);
int SetInsert(hset *s, char* src);
int SetErase(hset *s, char* src);
int SetClear(hset *s);
int SetFind(hset *s);
unsigned long SetSize(hset s);


#endif