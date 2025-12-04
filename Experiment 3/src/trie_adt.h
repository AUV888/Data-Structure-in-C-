#ifndef TRIE_ADT_H
#define TRIE_ADT_H

#include "trie.h"

int InitSet(tset s);
int DestroySet(tset s);
int SetInsert(tset s, int val);
int SetErase(tset s, int val);
int SetClear(tset s);
int SetFind(tset s);
unsigned long SetSize(tset s);

#endif