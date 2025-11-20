#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HTNode
{
    char data;
    int weight;
    struct HTNode *parent;
    struct HTNode *lchild;
    struct HTNode *rchild;
} HTNode, *HuffmanTree;

typedef struct
{
    char data;
    char *code;
} HCode;

HuffmanTree CreateHuffmanTree(char *chs, int *w, int n)
{
    if (n <= 0)
        return NULL;
    HuffmanTree *forest = (HuffmanTree *)malloc(n * sizeof(HuffmanTree));
    for (int i = 0; i < n; ++i)
    {
        HTNode *p = (HTNode *)malloc(sizeof(HTNode));
        p->data = chs[i];
        p->weight = w[i];
        p->parent = p->lchild = p->rchild = NULL;
        forest[i] = p;
    }
    int m = n;
    while (m > 1)
    {
        int i1 = -1, i2 = -1;
        for (int i = 0; i < m; ++i)
        {
            if (i1 == -1 || forest[i]->weight < forest[i1]->weight)
            {
                i2 = i1;
                i1 = i;
            }
            else if (i2 == -1 || forest[i]->weight < forest[i2]->weight)
            {
                i2 = i;
            }
        }
        HTNode *a = forest[i1], *b = forest[i2];
        HTNode *parent = (HTNode *)malloc(sizeof(HTNode));
        parent->data = '\0';
        parent->weight = a->weight + b->weight;
        parent->parent = NULL;
        parent->lchild = a;
        parent->rchild = b;
        a->parent = parent;
        b->parent = parent;

        forest[i1] = parent;
        forest[i2] = forest[m - 1];
        --m;
    }
    HuffmanTree root = forest[0];
    free(forest);
    return root;
}

void GenCodesDFS(HuffmanTree t, char *buf, int depth, HCode *table, int *k)
{
    if (!t)
        return;
    if (!t->lchild && !t->rchild)
    {
        table[*k].data = t->data;
        table[*k].code = (char *)malloc(depth + 1);
        memcpy(table[*k].code, buf, depth);
        table[*k].code[depth] = '\0';
        (*k)++;
        return;
    }
    buf[depth] = '0';
    GenCodesDFS(t->lchild, buf, depth + 1, table, k);
    buf[depth] = '1';
    GenCodesDFS(t->rchild, buf, depth + 1, table, k);
}

int GenerateCodeTable(HuffmanTree root, HCode *table, int maxn)
{
    if (!root)
        return 0;
    char buf[1024];
    int k = 0;
    GenCodesDFS(root, buf, 0, table, &k);
    return k <= maxn ? k : maxn;
}

void DestroyHuffmanTree(HuffmanTree t)
{
    if (!t)
        return;
    DestroyHuffmanTree(t->lchild);
    DestroyHuffmanTree(t->rchild);
    free(t);
}

int main(void)
{
    return 0;
}
