#include<stdio.h>
#include <string.h>

int strStr(char* haystack, char* needle);
//函数声明

int main() {
	char haystack[] = "hello";
	char needle[] = "ll";
	int result = strStr(haystack, needle);
	printf("%d\n", result);
	return 0;
}

int strStr(char* haystack, char* needle) {
	int m = strlen(haystack);
	//计算haystack的长度
	int n = strlen(needle);
	//计算needle的长度

	if (n == 0 || m == 0) { return 0; }
	//如果needle是空字符串或者haystack是空字符串，返回0
	if (m < n) { return -1; }
	//如果haystack的长度小于needle的长度，返回-1

	for (int i = 0; i <= m - n; i++) {
		//遍历haystack，直到m-n的位置
		for (int j = 0; j < n; j++) {
			//遍历needle，比较haystack和needle的字符
			if (haystack[i + j] != needle[j]) { break; }
			//如果haystack和needle的字符不匹配，跳出循环
			if (j == n - 1) { return i; }
			//如果haystack和needle的字符匹配，并且j已经到达needle的最后一个字符，返回i
		}
	}
	return -1;//如果遍历完haystack都没有找到needle，返回-1
}