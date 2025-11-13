#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#define MAX_STACK_SIZE 1000

typedef char ElemType;

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *left, *right;
} BiTNode, *BiTree;

int isOp(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '&' || x == '^' || x == '%')
        return 1;
    return 0;
}

BiTree RPN2Bitree(char *r)
{
    BiTree stack[MAX_STACK_SIZE];
    int top = -1;
    for (int i = 1; i <= r[0]; i++)
    {
        BiTree tnode = (BiTree)malloc(sizeof(BiTNode));
        tnode->data = r[i];
        tnode->left = NULL;
        tnode->right = NULL;
        if (isOp(tnode->data))
        {
            BiTree rightnode = stack[top];
            top--;
            BiTree leftnode = stack[top];
            top--;
            tnode->left = leftnode;
            tnode->right = rightnode;
        }
        top++;
        stack[top] = tnode;
    }
    return stack[0];
}
int PreOrderTraverse(BiTree bt) // PN
{
    if (bt == NULL)
        return 0;
    printf("%c ", bt->data);
    PreOrderTraverse(bt->left);
    PreOrderTraverse(bt->right);
    return 1;
}

int InOrderTraverse(BiTree bt) // MATH
{
    if (bt == NULL)
        return 0;
    InOrderTraverse(bt->left);
    printf("%c ", bt->data);
    InOrderTraverse(bt->right);
    return 1;
}

int PostOrderTraverse(BiTree bt) // RPN
{
    if (bt == NULL)
        return 0;
    PostOrderTraverse(bt->left);
    PostOrderTraverse(bt->right);
    printf("%c ", bt->data);
    return 1;
}
int main()
{
    char rpn1[] = {9, 'a', 'b', '+', 'c', '*', 'd', '-', 'e', '*'};
    char rpn2[] = {11, 'a', 'b', 'c', 'd', '-', '*', '+', 'e', 'f', '/', '-'};
    BiTree exp = RPN2Bitree(rpn2);
    InOrderTraverse(exp);
    return 0;
}