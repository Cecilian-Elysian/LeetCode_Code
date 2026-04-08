#include<stdio.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int compare(void const*  a, void const* b) {
	return (*(int*)a - *(int*)b);
}




int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    
}







int main() {
    int nums[] = { -1, 0, 1, 2, -1, -4 };
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;
    int* returnColumnSizes;

    int** result = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    // 打印结果
    printf("找到 %d 组解:\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("[%d, %d, %d]\n", result[i][0], result[i][1], result[i][2]);
        free(result[i]); // 释放每一行的内存
    }

    // 释放总内存
    free(result);
    free(returnColumnSizes);

    return 0;
}
