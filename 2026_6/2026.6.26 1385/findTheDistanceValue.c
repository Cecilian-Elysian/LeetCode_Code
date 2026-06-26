#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int findTheDistanceValue(int* arr1, int arr1Size, int* arr2, int arr2Size, int d) {
	qsort(arr1, arr1Size, sizeof(int), compare);
	qsort(arr2, arr2Size, sizeof(int), compare);

	int count = 0;
	for (int i = 0; i < arr1Size; i++) {
		int temp = 1;
		for (int j = 0; j < arr2Size; j++) {
			if (abs(arr1[i] - arr2[j]) <= d) {temp = 0; break;}
		}
		if (temp) { count++; temp = 0; }
	}
	return count;
}

int main() {
	int arr1[] = { 4, 5, 8 };
	int arr2[] = { 10, 9, 1, 8 };
	int d = 2;
	int result = findTheDistanceValue(arr1, sizeof(arr1) / sizeof(arr1[0]), arr2, sizeof(arr2) / sizeof(arr2[0]), d);
	printf("The distance value is: %d\n", result);
	return 0;
}