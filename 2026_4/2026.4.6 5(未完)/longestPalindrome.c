#include<stdio.h>
#include<string.h>
//动态规划
char* longestPalindrome(char* s) {
	int n = strlen(s);//字符串中字符个数
	if (s < 2) { return s; }
	int MaxLen = 1;
	int Start = 0;
	int** dp = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		dp[i] = (int*)malloc(sizeof(int) * n);
		memset(dp[i], 0, sizeof(int) * n);
		dp[i][i] = 1;//单个字符是回文串
	}

	for (int L = 2; L <= n; L++) {//L为子串长度
		for (int i = 0; i < n; i++) {
			int j = L + i - 1;//j为子串最后一个字符的索引
			if (j >= n) { break; }
			if (s[i] != s[j]) {
				dp[i][j] = 0;
			}
			else {
				if (L <= 3) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = dp[i + 1][j - 1];
				}
			}
			if (dp[i][j] && L > MaxLen) {
				MaxLen = L;
				Start = i;
			}
		}
	}



	
}