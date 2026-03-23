#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);                   //升序排序
}
int countUnique(int* arr, int len) {                //统计数组中不同元素的个数
	if (len == 0) return 0;                         //如果数组为空，返回0
	qsort(arr, len, sizeof(int), compare);          //排序数组
	int count = 1;                                  //至少有一个元素，所以初始值为1
    for (int i = 1; i < len; i++) {
        if (arr[i] != arr[i - 1]) {
            count++;
        }
    }
    return count;
}

long long maxSum(int* nums, int numsSize, int m, int k) {//滑动窗口
	long long ans = 0; //初始化答案为0
	long long currentSum = 0;//当前窗口的和
    for (int i = 0; i < k; i++) {
        currentSum += nums[i];
    }
    int* tempArr = (int*)malloc(k * sizeof(int));
    memcpy(tempArr, nums, k * sizeof(int)); 
    if (countUnique(tempArr, k) >= m) {
        ans = currentSum;
    }
    for (int right = k; right < numsSize; right++) {
		currentSum = currentSum - nums[right - k] + nums[right];    //更新窗口的和
		memmove(tempArr, tempArr + 1, (k - 1) * sizeof(int));       //移动数组元素
		tempArr[k - 1] = nums[right];                               //添加新元素
		if (countUnique(tempArr, k) >= m) {                         //判断不同元素个数是否满足要求
			ans = MAX(ans, currentSum);                             //更新答案
        }
    }
    free(tempArr); 
    return ans;
}