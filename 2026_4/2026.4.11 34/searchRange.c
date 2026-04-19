#include<stdio.h>
#include<stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int binarySearch(int* nums, int numsSize, int target, int extreme) {
	int left = 0, right = numsSize - 1;
	int ans = numsSize;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > target || (extreme && nums[mid] == target)) {
			right = mid - 1;
			ans = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return ans;
}


int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	int* res = (int*)malloc(sizeof(int) * 2);
	*returnSize = 2;
	res[0] = -1;
	res[1] = -1;
	if (numsSize == 0)return res;
	
	int leftIdx = binarySearch(nums, numsSize, target, 1);
	if (leftIdx == numsSize || nums[leftIdx] != target) return res;
	int rightIdx = binarySearch(nums, numsSize, target, 0) - 1;
	res[0] = leftIdx;
	res[1] = rightIdx;
	return res;
}


int main() {
	int nums[] = {5, 7, 7, 8, 8, 10};
	int returnSize;
	int* res = searchRange(nums, sizeof(nums) / sizeof(int), 8, &returnSize);
	printf("%d %d\n", res[0], res[1]);
	return 0;
}