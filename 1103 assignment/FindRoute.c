#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#define MAX_ROUTE_LENGTH 1000

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *left, *right;
} BiTNode, *BiTree;

int TreeHeight(BiTree b)
{
    if (!b)
        return 0;
    return 1 + (TreeHeight(b->left) > TreeHeight(b->right) ? TreeHeight(b->left) : TreeHeight(b->right));
}

void FindLongestRoute(BiTree curr, char **route)
{
    if (curr == NULL)
        return 0;
    int l_height = TreeHeight(curr->left);
    int r_height = TreeHeight(curr->right);
    if (l_height > r_height)
    {
        **route = 'L';
        (*route)++;
        FindLongestRoute(curr->left, route);
    }
    else
    {
        **route = 'R';
        (*route)++;
        FindLongestRoute(curr->right, route);
    }
}

int main()
{
    return 0;
}