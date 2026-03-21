#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//返回大小为*returnSize的数组的数组。数组的大小返回为*returnColumnSizes数组。
// 注意：返回的数组和*columnSizes数组都必须被malloced，假设调用方调用free（）。
//给你一个字符串数组，请你将  字母异位词  组合在一起。可以按任意顺序返回结果列表。  
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) 
{
	int n = **returnColumnSizes;
	for (int i = 0; i < strsSize; i++)
	{
		for(int j = i + 1; j < strsSize; j++)
		{
			if (strcmp(strs[i], strs[j]) == 0)
			{
				char** str[i][] = { strs[i], strs[j] };
			}
		}
	}
	int a = ()malloc(sizeof(char**) * n);
}