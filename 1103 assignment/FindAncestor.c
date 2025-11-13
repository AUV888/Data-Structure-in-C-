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

int FindChild(BiTree dest, BiTree curr, char **route, int **route_len)
{
    if (curr == NULL)
        return 0;
    if (curr == dest)
        return 1;
    if (curr->left != NULL)
    {
        **route = 'L';
        (*route)++;
        (*route_len)++;
        if (FindChild(dest, curr->left, route, route_len))
            return 1;
        (*route)--;
        (*route_len)--;
    }
    if (curr->right != NULL)
    {
        **route = 'R';
        (*route)++;
        (*route_len)++;
        if (FindChild(dest, curr->right, route, route_len))
            return 1;
        (*route)--;
        (*route_len)--;
    }
    return 0;
}

BiTree FindAncestor(BiTree root, BiTree dest1, BiTree dest2)
{
    char *r1 = (char *)malloc(MAX_ROUTE_LENGTH * sizeof(char)), *r2 = (char *)malloc(MAX_ROUTE_LENGTH * sizeof(char));
    int *rl1 = (int *)malloc(sizeof(int)), *rl2 = (int *)malloc(sizeof(int));
    *rl1 = 0;
    *rl2 = 0;
    FindChild(dest1, root, &r1, &rl1);
    FindChild(dest2, root, &r2, &rl2);
    BiTree target = root;
    for (int i = 0; i < *rl1 && i < *rl2; i++)
    {
        if (r1[i] != r2[i])
            break;
        else if (r1[i] == r2[i] && r2[i] == 'L')
            target = target->left;
        else if (r1[i] == r2[i] && r2[i] == 'R')
            target = target->right;
    }
    return target;
}

int main()
{
    return 0;
}