#ifndef TRIE_ADT_H
#define TRIE_ADT_H

#include "trie.h"

// int InitSet(tset s);
int tDestroySet(tset *s);
int tSetInsert(tset *s, char *src);
int tSetErase(tset *s, char *src);
// int tSetClear(tset s);
int tSetFind(tset s, char *src);
unsigned long tSetSize(tset s);
void tSetWildCardFind(tset s, char *src, char **res, int *retsize);

#endif