#include<stdio.h>
#include<string.h>

int function(char i)
{
	int count = 0;
	if (i == 'I') { count += 1; }
	if (i == 'V') { count += 5; }
	if (i == 'X') { count += 10; }
	if (i == 'L') { count += 50; }
	if (i == 'C') { count += 100; }
	if (i == 'D') { count += 500; }
	if (i == 'M') { count += 1000; }
	return count;
}
//int function(char c) 
//{
//	switch (c) 
//	{
//		case 'I': return 1;
//		case 'V': return 5;
//		case 'X': return 10;
//		case 'L': return 50;
//		case 'C': return 100;
//		case 'D': return 500;
//		case 'M': return 1000;
//		default: return 0; 
//	}
//}

int Special(char i, char j)
{
	int count = 0;
	if (i == 'I')
	{
		if(j == 'V')
		{
			count += 4;
		}
		else if (j == 'X')
		{
			count += 9;
		}
		else
		{
			return 0;
		}
	}

	if (i == 'X')
	{
		if (j == 'L')
		{
			count += 40;
		}
		else if (j == 'C')
		{
			count += 90;
		}
		else
		{
			return 0;
		}
	}

	if (i == 'C')
	{
		if (j == 'D')
		{
			count += 400;
		}
		else if (j == 'M')
		{
			count += 900;
		}
		else
		{
			return 0;
		}
	}
	return count;
}

int romanToInt(char* s) 
{
	int n = strlen(s);
	int num = 0;;
	
	for (int i = 0; i < n; i++)
	{
		if (i < n - 1) //确保i + 1是最后一个值
		{
			int spe = Special(s[i], s[i + 1]);
			if (spe > 0)
			{
				num += spe;
				i++;
				continue;
			}
		}
		num += function(s[i]);
	}
	return num;
}

int main()
{
	char s[20000];
	printf("请输入罗马数字: ");
	scanf("%s", s);

	int result = romanToInt(s);
	printf("结果: %d\n", result);

	return 0;
}