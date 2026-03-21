#include<stdio.h>

int sum(int num1, int num2);

int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	int a = sum(m, n);
	printf("%d", a);
}


int sum(int num1 ,int num2)
{
	int result = num1 + num2;
	return result;
}