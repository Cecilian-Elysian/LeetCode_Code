#include<stdio.h>
#include<math.h>

typedef struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
}Tree;


int maxDepth(struct TreeNode* root) 
{
	if (root == NULL)return 0;
	return 1 + fmax(maxDepth(root->left), maxDepth(root->right));
}
//return maxDepth(root->left) > maxDepth(root->right) : maxDepth(root->left), maxDepth(root->right);