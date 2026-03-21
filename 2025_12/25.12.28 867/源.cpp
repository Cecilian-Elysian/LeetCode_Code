#include<stdio.h>
#include<stdlib.h>

int main()
{
	return 0;
}

int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
	int m = matrixSize;//原矩阵的行数
	int n = *matrixColSize;//原矩阵的列数（基于行存在）
	*returnSize = n;//返回矩阵的行数
	*returnColumnSizes = (int*)malloc(sizeof(int) * n);//为返回矩阵列数分配内存
	int** ans = (int**)malloc(sizeof(int*) * n);//为返回矩阵分配内存
	for (int i = 0; i < n; i++)
	{
		(*returnColumnSizes)[i] = m;//保证每一行为m
		ans[i] = (int*)malloc(sizeof(int) * m);//为返回矩阵行数分配内存
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ans[j][i] = matrix[i][j];
		}
	}
	return ans;
}