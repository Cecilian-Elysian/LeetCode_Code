#include <stdio.h>
#include <string.h>
#include<stdlib.h>


int comp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int Unique(int* nums, int len) {
    int count = 1;
    qsort(nums, len, sizeof(int), comp);
    for (int i = 1; i < len; i++) {
        if (nums[i- 1] != nums[i]) { count++; }
    }
    return count;
}

long long maximumSubarraySum(int* nums, int numsSize, int k) {
    long long ans = 0;
    long long current = 0;
    //创建一份大小为k的窗口
    for (int i = 0; i < k; i++) {
        current += nums[i];
    }
    if (Unique(nums, k) == k) {
        ans = current;
    }
    //滑动窗口
    int* tempArr = (int*)malloc(k * sizeof(int));
    memcpy(tempArr, nums, k * sizeof(int));
    for (int i = k; i < numsSize; i++) {
        current = current - tempArr[i - k] + tempArr[i];
        if (Unique(tempArr, k) == k) {
            ans = current;
         }
    }
    free(tempArr);
    return ans;
}


int main() {
    return 0;
}