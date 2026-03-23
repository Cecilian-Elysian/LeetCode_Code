#include<stdio.h>
/*
给你一个由 n 个元素组成的整数数组 nums 和一个整数 k 。
请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数。
*/

#define MAX(a, b) ((a) > (b) ? (a) : (b))

double findMaxAverage(int* nums, int numsSize, int k) {
	long long sum = 0;                                      // 使用 long long 来避免整数溢出
	for (int i = 0; i < k; i++) {                           // 计算前 k 个元素的和
		sum += nums[i];                                     // 更新窗口的和
    }

	double maxAvg = (double)sum / k;                        // 初始化最大平均数
    
	for (int right = k; right < numsSize; right++) {        // 从第 k 个元素开始，使用滑动窗口更新 sum 和 maxAvg
		sum += nums[right] - nums[right - k];               // 更新窗口的和
		double avg = (double)sum / k;                       // 计算当前窗口的平均数
		maxAvg = MAX(maxAvg, avg);                          // 更新最大平均数
    }

    return maxAvg;
}

int main() {
    int nums[] = { 1, 12, -5, -6, 50, 3 };
    int k = 4;
    int numsSize = sizeof(nums) / sizeof(int);

    printf("%.6lf\n", findMaxAverage(nums, numsSize, k));

    return 0;
}