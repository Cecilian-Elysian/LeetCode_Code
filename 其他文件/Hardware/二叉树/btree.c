#include "btree.h"

// 1. 创建新节点
BTNode* BuyNode(BTDataType x) {
    BTNode* node = (BTNode*)malloc(sizeof(BTNode));
    if (node == NULL) {
        perror("malloc failed");
        exit(-1); // 内存分配失败直接退出
    }
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 2. 插入节点 (递归实现)
// 逻辑：如果树空则创建根；如果 x < 当前值往左插；如果 x > 当前值往右插
void BTreeInsert(BTNode** root, BTDataType x) {
    // 如果当前节点为空，说明找到了插入位置
    if (*root == NULL) {
        *root = BuyNode(x);
        return;
    }

    // 如果数据已存在，不重复插入（或者根据需要修改逻辑）
    if ((*root)->data == x) {
        return;
    }
    
    // 根据大小决定往左还是往右
    if (x < (*root)->data) {
        BTreeInsert(&(*root)->left, x);
    } else {
        BTreeInsert(&(*root)->right, x);
    }
}

// 3. 查找节点
BTNode* BTreeFind(BTNode* root, BTDataType x) {
    if (root == NULL) {
        return NULL;
    }
    
    if (root->data == x) {
        return root;
    }
    
    // 递归查找左右子树
    if (x < root->data) {
        return BTreeFind(root->left, x);
    } else {
        return BTreeFind(root->right, x);
    }
}

// 4. 前序遍历
void BTreePreOrder(BTNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);      // 访问根
    BTreePreOrder(root->left);      // 遍历左
    BTreePreOrder(root->right);     // 遍历右
}

// 5. 中序遍历
void BTreeInOrder(BTNode* root) {
    if (root == NULL) {
        return;
    }
    BTreeInOrder(root->left);       // 遍历左
    printf("%d ", root->data);      // 访问根
    BTreeInOrder(root->right);      // 遍历右
}

// 6. 计算叶子节点个数
int BTreeLeafSize(BTNode* root) {
    if (root == NULL) {
        return 0;
    }
    // 如果是叶子节点 (左右孩子都为空)
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    // 否则 = 左子树叶子数 + 右子树叶子数
    return BTreeLeafSize(root->left) + BTreeLeafSize(root->right);
}

// 7. 计算树的高度
int BTreeHeight(BTNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = BTreeHeight(root->left);
    int rightHeight = BTreeHeight(root->right);
    
    // 高度 = 左右子树最大高度 + 1 (根节点本身)
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 8. 销毁二叉树 (后序遍历销毁)
// 必须先销毁孩子，再销毁根，否则找不到孩子了
void BTreeDestroy(BTNode** root) {
    if (*root == NULL) {
        return;
    }
    // 1. 销毁左子树
    BTreeDestroy(&(*root)->left);
    // 2. 销毁右子树
    BTreeDestroy(&(*root)->right);
    // 3. 释放根节点
    free(*root);
    *root = NULL; // 防止野指针
}