#ifndef TRIE_H
#define TRIE_H

typedef struct TNODE
{
    char d;
    struct TNODE *sib;
    struct TNODE *next;
} tnode;

typedef tnode *tset;

#endif