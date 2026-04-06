#include<stdio.h>

int searchInsert(int* n, int nS, int t);

int main() {
        // 测试用例 1: 目标值在数组中间
        int nums1[] = { 1, 3, 5, 6 };
        int size1 = sizeof(nums1) / sizeof(nums1[0]);
        int target1 = 5;
        // 预期输出: 2
        printf("测试 1 (目标 %d): 返回索引 %d\n", target1, searchInsert(nums1, size1, target1));

        // 测试用例 2: 目标值需要插入 (比现有元素小)
        int nums2[] = { 1, 3, 5, 6 };
        int size2 = sizeof(nums2) / sizeof(nums2[0]);
        int target2 = 2;
        // 预期输出: 1
        printf("测试 2 (目标 %d): 返回索引 %d\n", target2, searchInsert(nums2, size2, target2));

        // 测试用例 3: 目标值比所有元素都大 (插入末尾)
        int nums3[] = { 1, 3, 5, 6 };
        int size3 = sizeof(nums3) / sizeof(nums3[0]);
        int target3 = 7;
        // 预期输出: 4
        printf("测试 3 (目标 %d): 返回索引 %d\n", target3, searchInsert(nums3, size3, target3));

        // 测试用例 4: 目标值比所有元素都小 (插入开头)
        int nums4[] = { 1, 3, 5, 6 };
        int size4 = sizeof(nums4) / sizeof(nums4[0]);
        int target4 = 0;
        // 预期输出: 0
        printf("测试 4 (目标 %d): 返回索引 %d\n", target4, searchInsert(nums4, size4, target4));

        return 0;
 }

int searchInsert(int* nums, int numsSize, int target) {
	for (int i = 0; i < numsSize; i++) {
		if (target <= nums[i]) {
			return i;
		}
	}
	return numsSize;
}

