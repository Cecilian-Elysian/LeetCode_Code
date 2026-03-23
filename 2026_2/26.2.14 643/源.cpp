#include<stdio.h>
#define MAX(a, b) (((a) > (b)) ? a: b)
double findMaxAverage(int* nums, int numsSize, int k) {
	double ans = -99999999999999;
	double count = 0;
	for (int i = 0; i < k; i++) {
		count += nums[i];
	}
	ans = MAX(ans, (count / k));
	for (int i = k; i < numsSize; i++) {
		int left = i - k;
		count = count + nums[i] - nums[left];
		ans = MAX(ans, (count / k));
	}
	return ans;
}

int main() {
	return 0;
}