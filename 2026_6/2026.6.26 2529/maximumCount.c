#include <stdio.h>
//两次二分查找,一次找负数的个数,一次找正数的个数,返回两者中较大的一个
int maximumCount(int* nums, int numsSize) {
	
	if (numsSize == 0) { return 0; }
	if (nums[0] == 0 && nums[numsSize - 1] == 0) return 0; // 立即返回0
	if (nums[0] > 0) { return numsSize; }
	if (nums[numsSize - 1] < 0) { return numsSize; }

	int left = 0;
	int right = numsSize - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] < 0) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	int neg = left;

	left = 0, right = numsSize - 1;
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] <= 0) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	int pos = numsSize - left;
	int result = (pos > neg) ? pos : neg;
	return result;
}

int main() {
	int nums[] = { -3, -2, -1, 0, 1, 2, 3 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int result = maximumCount(nums, numsSize);
	printf("Maximum count: %d\n", result);
	return 0;
}