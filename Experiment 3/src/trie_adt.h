#ifndef TRIE_ADT_H
#define TRIE_ADT_H

#include "trie.h"

// int InitSet(tset s);
int tDestroySet(tset *s);
int tSetInsert(tset *s, char *src);
/*
 *@brief Nothing Different with tSetFind, just change '\0' to 1 to mark the deletion but not really delete it!
 */
int tSetErase(tset *s, char *src);
// int tSetClear(tset s);
/*@return Search Length
 */
int tSetFind(tset s, char *src);
unsigned long tSetSize(tset s);

#endif