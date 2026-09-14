#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help(char* s, int N, int left, int right, int* start, int* len) {
	while (left >= 0 && right < N && s[left] == s[right])// 扩展回文子串
        left--, right++;
    if (right - left - 1 > *len) {  // 如果找到更长的子串，保存其信息
		*start = left + 1;// 更新起始位置
		*len = right - left - 1;// 更新长度
    }
}


char* longestPalindrome(char* s) {
    int N = strlen(s), start = 0, len = 0;

    // 1. 寻找最长回文子串的起始位置和长度
    for (int i = 0; i < N; i++)
        help(s, N, i - 1, i + 1, &start, &len); // 奇数
    for (int i = 0; i < N; i++)
        help(s, N, i, i + 1, &start, &len);   // 偶数

    // 2. 动态分配内存并拷贝结果 (避免修改原字符串)
    char* result = (char*)malloc(len + 1);
    if (result == NULL) return NULL; // 内存分配失败处理

    strncpy_s(result, len + 1, s + start, len);
    result[len] = '\0';

    return result;
}

int main() {
	char s[] = "babad";
	char* result = longestPalindrome(s);
	if (result != NULL) {
		printf("Longest Palindromic Substring: %s\n", result);
		free(result); // 释放动态分配的内存
	}
	else {
		printf("Memory allocation failed.\n");
	}
	return 0;
}