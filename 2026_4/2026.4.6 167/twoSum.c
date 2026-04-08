#include<stdio.h>
#include<stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
	int l = 0, r = numbersSize - 1;
	while (1) {
		if (numbers[l] + numbers[r] > target) { r -= 1; }
		if (numbers[l] + numbers[r] < target) { l += 1; }
		if (numbers[l] + numbers[r] == target) {
			int* nums = (int*)malloc(sizeof(int) * 2);
			nums[0] = l + 1;
			nums[1] = r + 1;
			*returnSize = 2;
			return nums;
			free(nums);
		}
	}
}

int main() {
	int numbers[] = { 2, 7, 11, 15 };
	int target = 9;
	int returnSize;
	int* result = twoSum(numbers, sizeof(numbers) / sizeof(int), target, &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%d ", result[i]);
	}
	free(result);
	return 0;
}