#define ElemType int
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *left, *right;
} BiTNode, *BiTree;

int Is_BST(BiTree b)
{
    if (!b)
        return 1;
    else if (!b->left && !b->right)
        return 1;
    else if (b->left && !b->right && b->left->data < b->data && Is_BST(b->left))
        return 1;
    else if (!b->left && b->right && b->right->data > b->data && Is_BST(b->right))
        return 1;
    else if (b->left && b->right && Is_BST(b->left) && Is_BST(b->right) && b->left->data < b->data && b->right->data > b->data)
        return 1;
    else
        return 0;
}

int main()
{
    return 0;
}