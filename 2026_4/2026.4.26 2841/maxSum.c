#include <stdio.h>
#include <stdlib.h>

long long maxSum(int* nums, int numsSize, int m, int k) {
    if (numsSize < k) return 0;
    int* freq = (int*)calloc(1000000001, sizeof(int));
    if (!freq) return 0;
    long long sum = 0;
    int uniq = 0;
    long long best = 0;
    for (int i = 0; i < k; i++) {
        if (freq[nums[i]] == 0) uniq++;
        freq[nums[i]]++;
        sum += nums[i];
    }
    if (uniq >= m && sum > best) best = sum;
    for (int i = k; i < numsSize; i++) {
        freq[nums[i - k]]--;
        if (freq[nums[i - k]] == 0) uniq--;
        sum -= nums[i - k];
        if (freq[nums[i]] == 0) uniq++;
        freq[nums[i]]++;
        sum += nums[i];
        if (uniq >= m && sum > best) best = sum;
    }
    free(freq);
    return best;
}

int main() {
    int a1[] = {2, 6, 7, 3, 1, 7};
    printf("%lld\n", maxSum(a1, 6, 3, 4));
    int a2[] = {5, 9, 9, 2, 4, 5, 4};
    printf("%lld\n", maxSum(a2, 7, 1, 3));
    int a3[] = {1, 2, 1, 2, 1, 2, 1};
    printf("%lld\n", maxSum(a3, 7, 3, 3));
    return 0;
}
