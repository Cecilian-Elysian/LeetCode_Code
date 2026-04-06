#include <stdio.h>
#include <stdlib.h>

//定义二叉树
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//分配内存
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = malloc(sizeof *newNode);
    if (!newNode) {
        fprintf(stderr, "内存分配失败！\n");
        exit(1);
    }
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//递归函数
void inorderTraversal(const struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

//清理内存
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

//主函数
int main(void) {
    // 构建如下二叉树:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5

    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    freeTree(root);
    return 0;
}