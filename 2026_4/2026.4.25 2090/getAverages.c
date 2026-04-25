#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    int* avgs = (int*)malloc(sizeof(int) * numsSize);
	// 设置返回数组的大小

    *returnSize = numsSize;
	// 初始化返回数组，默认值为 -1

    memset(avgs, -1, numsSize * sizeof(int));
	// 如果数组长度小于 2 * k + 1，无法计算平均值，直接返回

    if (numsSize < 2 * k + 1) {
		free(avgs);
        // 释放动态分配的内存
        return avgs;
    }
	int left = 0, mid = k, right = 2 * k;
    // 定义窗口的左右边界和中间位置

	long long count = 0;
    // 使用 long long 类型来避免整数溢出
   
	for (int i = 0; i <= right; i++) {
        // 计算第一个窗口的和
        count += nums[i];
    }
	avgs[mid] = count / (2 * k + 1);
    // 计算第一个窗口的平均值

	while (right < numsSize - 1) {
        // 滑动窗口，更新左右边界和中间位置
        
		right += 1, left += 1, mid += 1;
        // 移动窗口

		count = count + nums[right] - nums[left - 1];
        // 更新窗口的和

		avgs[mid] = count / (2 * k + 1);
        // 计算当前窗口的平均值
    }
    return avgs;
}


int main() {
    int nums[] = { 7,4,3,9,1,8,5,2,6 };
    int k = 3;
    int returnSize;
    int* avgs = getAverages(nums, sizeof(nums) / sizeof(int), k, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", avgs[i]);
    }
    printf("\n");
    // 释放动态分配的内存
    free(avgs);
    return 0;
}
