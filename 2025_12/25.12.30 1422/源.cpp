#include<stdio.h>
#include<string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxScore(char* s)
{
	int n = strlen(s);
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		int result = 0;
		for (int j = 0; j < i; j++)
		{
			if (s[j] == '0')
			{
				result++;
			}
		}
		for (int j = i; j < n; j++)
		{
			if (s[j] == '1')
			{
				result++;
			}
		}
		ans = MAX(ans, result);
	}
	return ans;
}


int main()
{
	char s[10000];
	scanf("%s", &s);
	int a = maxScore(s);
	printf("%d", a);
	return 0;
}