#include<stdio.h>
#include<stdbool.h>


typedef struct TreeNode {
	int data;
	struct TreeNode *l, *r;
}TreeNode;



bool checkTree(TreeNode * root)
{
	if (root == NULL || root->l == NULL || root->r == NULL)
	{
		return 0;
	}
	else(root->data == root->l->data + root->r->data);
		return 1;
}


int main()
{
	return 0;
}

