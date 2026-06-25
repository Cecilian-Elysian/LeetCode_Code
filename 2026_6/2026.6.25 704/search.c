#include <stdio.h>

int search(int* nums, int numsSize, int target) {
	int left = 0, right = numsSize - 1;
	if (target > nums[right] || target < nums[left]) {
		return -1;
	}
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] > target) { 
			right = mid - 1;
			continue;
		}
		else if (nums[mid] < target) {
			left = mid + 1;
			continue;
		}
		else if (nums[mid] == target) {
			return mid;
		}
	}
	return -1;
}

int main() {
	int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int target = 5;
	int index = search(nums, sizeof(nums) / sizeof(nums[0]), target);
	if (index != -1) {
		printf("Found %d at index %d\n", target, index);
	}
	else {
		printf("%d not found in the array\n", target);
	}
	return 0;
}