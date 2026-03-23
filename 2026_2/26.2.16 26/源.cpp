#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    int slow = 0;
    for (int fast = 1; fast < numsSize; fast++) {  
        if (nums[fast] != nums[slow]) {
            slow++; 
            nums[slow] = nums[fast]; 
        }
    }
    return slow + 1;
}


int main() {
	int nums[] = { 1, 1, 2, 2, 2, 3, 4 };
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int ans = removeDuplicates(nums, numsSize);
	printf("%d\n", ans);
	return 0;
}