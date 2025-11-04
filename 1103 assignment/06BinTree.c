// VS中使用传统C不安全的函数时，增加下面的宏定义关闭VS编译报错
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

typedef char ElemType;

// 二叉树的链式存储实现，基本操作函数定义
//  参考严蔚敏教材，P127，定义结点的类型
// 结点的存储结构
typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *left, *right; // 左右孩子指针
} BiTNode, *BiTree;               //

// 1. 初始化二叉链式存储的二叉树，采用无头结点的方式初始化
BiTree InitBinTree();

// 2. 销毁二叉链式存储的二叉树，释放每个结点所分配的内存
//    注意是没有头结点的二叉树
int DestroyBinTree(BiTree bt);

// 3.1 从先序遍历的字符串中创建二叉树，将创建的二叉树用返回值返回到调用者
//     先序遍历的字符串中用字符'!'表示空结点
// 参考教材 P131 实现，这里的参数nStringStart，表示创建树时，从preordString的那个字符开始读入
// 使用引用形式的参数传递方式进行参数传递，这样可以在递归调用时，每读入一个字符后，
//  nStringStart向后移动一个位置，并将这个值的改变带回到调用者
BiTree CreateBinTree(char *preordString, int *nStringStart);

// 4.1 先序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int PreOrderTraverse(BiTree bt);

// 4.2 中序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int InOrderTraverse(BiTree bt);

// 4.3 后序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int PostOrderTraverse(BiTree bt);

// 4.4 层序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int LevelOrderTraverse(BiTree bt);

// 5 计算树的结点数目
int BiTreeNodeCount(BiTree bt);

// 6 计算树的叶子结点数目
int BiTreeLeavesCount(BiTree bt);

// 7 计算树的层数
int BiTreeLevelCount(BiTree bt);

int main()
{

    BiTree bt1 = InitBinTree();
    BiTree bt2 = InitBinTree();

    char sTree1[] = "BC!D!!E!!";
    char sTree2[] = "FGI!!!HJ!!K!!";

    printf("\n从先序遍历结果  %s  创建第一棵二叉树\n", sTree1);
    int nStringStart = 0;
    bt1 = CreateBinTree(sTree1, &nStringStart);

    printf("\n第一棵树的先序遍历：\n");
    PreOrderTraverse(bt1);
    printf("\n第一棵树的中序遍历：\n");
    InOrderTraverse(bt1);
    printf("\n第一棵树的后序遍历：\n");
    PostOrderTraverse(bt1);
    printf("\n第一棵树的层序遍历：\n");
    LevelOrderTraverse(bt1);
    printf("\n第一棵树的结点数为：%d\n\n第一棵树的叶子结点数为：%d\n\n第一棵树的层数为：%d\n",
           BiTreeNodeCount(bt1), BiTreeLeavesCount(bt1), BiTreeLevelCount(bt1));

    printf("\n从先序遍历结果  %s  创建第二棵二叉树\n", sTree2);
    nStringStart = 0;
    bt2 = CreateBinTree(sTree2, &nStringStart);

    printf("\n第二棵树的先序遍历：\n");
    PreOrderTraverse(bt2);
    printf("\n第二棵树的中序遍历：\n");
    InOrderTraverse(bt2);
    printf("\n第二棵树的后序遍历：\n");
    PostOrderTraverse(bt2);
    printf("\n第二棵树的层序遍历：\n");
    LevelOrderTraverse(bt2);
    printf("\n第二棵树的结点数为：%d\n\n第二棵树的叶子结点数为：%d\n\n第二棵树的层数为：%d\n",
           BiTreeNodeCount(bt2), BiTreeLeavesCount(bt2), BiTreeLevelCount(bt2));

    printf("\n将第一棵树销毁\n");
    DestroyBinTree(bt1);
    printf("\n将第二棵树销毁\n");
    DestroyBinTree(bt2);

    return 0;
}

// 1. 初始化二叉链式存储的二叉树，采用无头结点的方式初始化
BiTree InitBinTree()
{
    return NULL;
}

// 2. 销毁二叉链式存储的二叉树，释放每个结点所分配的内存
//    注意是没有头结点的二叉树
int DestroyBinTree(BiTree bt)
{
    if (bt == NULL)
        return 0;
    DestroyBinTree(bt->left);
    DestroyBinTree(bt->right);
    free(bt);
    return 1;
}

// 3.1 从先序遍历的字符串中创建二叉树，将创建的二叉树用返回值返回到调用者
//     先序遍历的字符串中用字符'!'表示空结点
BiTree CreateBinTree(char *preordString, int *nStringStart)
{
    // 将下面的代码修改为正确的代码
    return NULL;
}

// 4.1 先序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int PreOrderTraverse(BiTree bt)
{
    if (bt == NULL)
        return 0;
    printf("%c ", bt->data);
    PreOrderTraverse(bt->left);
    PreOrderTraverse(bt->right);
    return 1;
}

// 4.2 中序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int InOrderTraverse(BiTree bt)
{
    if (bt == NULL)
        return 0;
    InOrderTraverse(bt->left);
    printf("%c ", bt->data);
    InOrderTraverse(bt->right);
    return 1;
}

// 4.3 后序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int PostOrderTraverse(BiTree bt)
{
    if (bt == NULL)
        return 0;
    PostOrderTraverse(bt->left);
    PostOrderTraverse(bt->right);
    printf("%c ", bt->data);
    return 1;
}

// 4.4 层序遍历二叉树，将结果输出到控制台（stdc::out）
//    返回值：空树返回false，非空树返回true
int LevelOrderTraverse(BiTree bt)
{
    // 将下面的代码修改为正确的代码
    return 0;
}

// 5 计算树的结点数目
int BiTreeNodeCount(BiTree bt)
{
    // 将下面的代码修改为正确的代码
    return 0;
}

// 6 计算树的叶子结点数目
int BiTreeLeavesCount(BiTree bt)
{
    // 将下面的代码修改为正确的代码
    return 0;
}

// 7 计算树的层数
int BiTreeLevelCount(BiTree bt)
{
    // 将下面的代码修改为正确的代码
    return 0;
}