#include<stdio.h>
#include<stdlib.h>

int* getConcatenation(int* nums, int numsSize, int* returnSize)
{
	int n = numsSize;
	int* ans = (int*)malloc(sizeof(int) * 2 * n);
	*returnSize = 2 * n;
	for (int i = 0; i < n; i++)
	{
		ans[i] = nums[i];
		ans[n + i] = nums[i];
	}
	return ans;
}

int main() 
{
    int nums[] = { 1, 2, 3 };
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int* result = getConcatenation(nums, numsSize, &returnSize);

    if (result != NULL) {
        printf("串联后的数组: ");
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }
    return 0;
}