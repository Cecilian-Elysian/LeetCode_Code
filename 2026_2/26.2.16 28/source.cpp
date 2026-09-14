#include <stdio.h>
#include <string.h>

int strStr(char* haystack, char* needle) {
    int n = (int)strlen(haystack);
    int m = (int)strlen(needle);
    if (m == 0) return 0;
    if (n < m) return -1;
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && haystack[i + j] == needle[j]) j++;
        if (j == m) return i;
    }
    return -1;
}

int main() {
    printf("%d\n", strStr("sadbutsad", "sad"));
    printf("%d\n", strStr("leetcode", "leeto"));
    printf("%d\n", strStr("hello", "ll"));
    printf("%d\n", strStr("", "a"));
    return 0;
}
