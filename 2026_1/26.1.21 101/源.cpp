#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};


bool isMirror(struct TreeNode* p, struct TreeNode* q)
{
	if (p->val == NULL && q->val == NULL)return true;
	if (p->val == NULL || q->val == NULL)return false;

	return(p->val == q->val)
		&& (p->left , q->right)
		&& (q->right , q->left);
}


bool isSymmetric(struct TreeNode* val) 
{
	if (val == NULL) return true;
	return isMirror(val->left,val->right);
}

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


int main() {
    // 测试案例 1: 对称的树
    //       1
    //      / \
    //     2   2
    //    / \ / \
    //   3  4 4  3
    struct TreeNode* root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(2);
    root1->left->left = createNode(3);
    root1->left->right = createNode(4);
    root1->right->left = createNode(4);
    root1->right->right = createNode(3);

    if (isSymmetric(root1)) {
        printf("测试案例 1: 这是一棵对称的二叉树\n");
    }
    else {
        printf("测试案例 1: 这不是对称的二叉树\n");
    }

    // 测试案例 2: 不对称的树
    //       1
    //      / \
    //     2   2
    //      \   \
    //       3   3
    struct TreeNode* root2 = createNode(1);
    root2->left = createNode(2);
    root2->right = createNode(2);
    root2->left->right = createNode(3);
    root2->right->right = createNode(3);

    if (isSymmetric(root2)) {
        printf("测试案例 2: 这是一棵对称的二叉树\n");
    }
    else {
        printf("测试案例 2: 这不是对称的二叉树\n");
    }

    // 注意：实际项目中需要释放 malloc 分配的内存，这里为了演示省略了 free
    return 0;
}