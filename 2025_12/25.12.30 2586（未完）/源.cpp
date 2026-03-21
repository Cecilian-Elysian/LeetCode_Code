#include<stdio.h>
#include<string.h>

int main()
{
	return 0;
}

int vowelStrings(char** words, int wordsSize, int left, int right)
{
	int count = 0;
	for (int i = left; i <= right && i <= wordsSize ; i++)
	{
		int m = strlen(words[i]);//第i个单词的长度
		if (m == 0) continue;
		char b = words[i][0];//第i个单词第一个字符
		char c = words[i][m - 1];//第i个单词最后一个字符
			if (b == 'a' || b == 'e' || b == 'i' || b == 'u' || b == 'o')
			{
				if (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o')
					count++;
			}
	}
	return count;
}