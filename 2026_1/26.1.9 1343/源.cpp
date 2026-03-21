#include<stdio.h>

/*
*给你一个整数数组?arr?和两个整数 k?和 threshold?。 请你返回长度为 k?且平均值大于等于?threshold?的子数组数目。
* arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
*/


int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
	int temp = 0;
	for (int i = 0; i < k; i++) {
		temp = temp + arr[i];
	}
	int count = 0;
	if (temp / k >= threshold) {
		count++;
	}
	for (int i = k; i < arrSize; i++) {
		temp = temp - arr[i - k] + arr[i];
		if(temp / k >= threshold) {
			count++;
		}
	}
	return count;
}
int main() {
	int arr[] = { 2,2,2,2,5,5,5,8 };
	int k = 3;
	int threshold = 4;
	int result = numOfSubarrays(arr, sizeof(arr) / sizeof(int), k, threshold);
	printf("%d", result);
	return 0;
}