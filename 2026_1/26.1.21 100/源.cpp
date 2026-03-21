#include<stdio.h>
#include<stdbool.h>

struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
};
struct TreeNode Tree1;
struct TreeNode Tree2;

bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
	if (p == NULL && q == NULL) return true;
	if (p == NULL || q == NULL) return false;
	return (p->data == q->data) &&
		isSameTree(p->left, q->left) &&
		isSameTree(p->right, q->right);
}



int main() {
	// 构建 Tree1 和 Tree2（示例：手动创建节点）
	struct TreeNode* root1 = &Tree1;
	struct TreeNode* root2 = &Tree2;
	// 初始化节点（如 root1->data=1; root1->left=...）
	bool result = isSameTree(root1, root2);
	printf("两棵树是否相同？%s\n", result ? "是" : "否");
	return 0;
}