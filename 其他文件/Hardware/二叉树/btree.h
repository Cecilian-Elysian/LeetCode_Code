#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义数据类型，方便以后修改（比如改成 float 或 char）
typedef int BTDataType;

// 定义二叉树节点结构体
typedef struct BinaryTreeNode {
    BTDataType data;              // 数据域
    struct BinaryTreeNode* left;  // 左孩子指针
    struct BinaryTreeNode* right; // 右孩子指针
} BTNode;

/**
 * 创建新节点
 * @param x 数据
 * @return 新节点的指针
 */
BTNode* BuyNode(BTDataType x);

/**
 * 插入节点 (构建二叉搜索树逻辑: 左小右大)
 * @param root 根节点指针的地址 (二级指针，因为可能修改根节点)
 * @param x 要插入的数据
 */
void BTreeInsert(BTNode** root, BTDataType x);

/**
 * 查找节点
 * @param root 根节点
 * @param x 要查找的数据
 * @return 找到的节点指针，未找到返回 NULL
 */
BTNode* BTreeFind(BTNode* root, BTDataType x);

/**
 * 前序遍历 (根 -> 左 -> 右)
 */
void BTreePreOrder(BTNode* root);

/**
 * 中序遍历 (左 -> 根 -> 右) - 对于二叉搜索树，这是有序输出
 */
void BTreeInOrder(BTNode* root);

/**
 * 获取叶子节点个数
 */
int BTreeLeafSize(BTNode* root);

/**
 * 获取树的高度 (深度)
 */
int BTreeHeight(BTNode* root);

/**
 * 销毁二叉树 (释放所有内存)
 * @param root 根节点指针的地址
 */
void BTreeDestroy(BTNode** root);

#endif // BTREE_H