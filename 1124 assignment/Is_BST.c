#define ElemType int
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *left, *right;
} BiTNode, *BiTree;

void In_Order_Traverse(BiTree b, int *result, int *len)
{
    if (!b)
        return;
    In_Order_Traverse(b->left, result, len);
    result[*len] = b->data;
    (*len)++;
    In_Order_Traverse(b->right, result, len);
    return;
}

int Is_BST(BiTree b)
{
    int result[10000], len = 0, glob_max = 0x80000000;
    In_Order_Traverse(b, result, &len);
    for (int i = 0; i < len; i++)
    {
        if (result[i] <= glob_max)
            return 0;
        else
            glob_max = result[i];
    }
    return 1;
}

int main()
{
    return 0;
}