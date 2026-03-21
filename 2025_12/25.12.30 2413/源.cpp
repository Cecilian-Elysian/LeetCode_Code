#include<stdio.h>

int smallestEvenMultiple(int n);

int main()
{
	int n;
	scanf("%d", &n);
	int result = smallestEvenMultiple(n);
	printf("%d", result);
}

int smallestEvenMultiple(int n)
{
	if(n % 2 == 0)
	{
		return n;
	}
	else
	{
		return (2 * n);
	}
}

