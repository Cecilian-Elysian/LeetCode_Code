#include<stdio.h>

int mySqrt(int x) {
	if (x == 0 || x == 1) {
		return x;
	}
	int left = 1, right = x, ans = 0;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (mid > x / mid) {
			right = mid - 1;
		}
		if (mid < x / mid) {
			ans = mid;	
			left = mid + 1;
		}
		if (mid == x / mid) {
			return mid;
		}

	}
	return ans;
}


int main() {
	int x = 9;
	int res = mySqrt(x);
	printf("%d\n", res);
	return 0;
}
