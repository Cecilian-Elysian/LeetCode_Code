#include<stdio.h>

//f(n) = f(n-1) + f(n-2)
int climbStairs(int n) {

	int prev = 1, prev_prev = 2, currunt = 0;

	if (n <= 0)return 0;
	//n=0时没有台阶，不能爬
	if (n == 1)return prev;
	//n=1时只有一个台阶，只有一种爬法
	if (n == 2)return prev_prev;
	//n=2时有两个台阶，有两种爬法

	for (int i = 3; i <= n; i++) {

		currunt = prev + prev_prev;
		//当前台阶的爬法等于前一个台阶的爬法加上前两个台阶的爬法
		prev = prev_prev;
		//更新前一个台阶的爬法为前两个台阶的爬法
		prev_prev = currunt;
		//更新前两个台阶的爬法为当前台阶的爬法
	}
	return currunt;
}

int main() {
	int n = 5;
	int result = climbStairs(n);
	printf("%d\n", result);
	return 0;
}