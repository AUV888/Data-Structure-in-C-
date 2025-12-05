#include "trie.h"
#include <stdlib.h>

tset create_tset(void)
{
    tset newnode = (tset)malloc(sizeof(tnode));
    return newnode;
}