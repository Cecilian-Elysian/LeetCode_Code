#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* longestPalindrome(char* s) {
    int n = strlen(s);
    if (n < 2) return s;

    int MaxLen = 1;
    int Start = 0;
    int** dp = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc(sizeof(int) * n);
        memset(dp[i], 0, sizeof(int) * n);
        dp[i][i] = 1;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i < n; i++) {
            int j = L + i - 1;
            if (j >= n) break;
            if (s[i] != s[j]) {
                dp[i][j] = 0;
            } else {
                if (L <= 3) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }
            if (dp[i][j] && L > MaxLen) {
                MaxLen = L;
                Start = i;
            }
        }
    }

    char* result = (char*)malloc(sizeof(char) * (MaxLen + 1));
    memcpy(result, s + Start, MaxLen);
    result[MaxLen] = '\0';

    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
    return result;
}

int main() {
    char* r;
    r = longestPalindrome("babad");
    printf("%s\n", r);
    free(r);
    r = longestPalindrome("cbbd");
    printf("%s\n", r);
    free(r);
    r = longestPalindrome("a");
    printf("%s\n", r);
    free(r);
    r = longestPalindrome("ac");
    printf("%s\n", r);
    free(r);
    return 0;
}
