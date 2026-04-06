#include<stdio.h>

int lengthOfLongestSubstring(char* s) {
	int maxLength = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		int length = 0;
		for(int j = i; s[j] != '\0'; j++) {
			int k;
			for(k = i; k < j; k++) {
				if(s[k] == s[j]) {
					break;
				}
			}
			if(k < j) {
				break;
			}
			length++;
		}
		if(length > maxLength) {
			maxLength = length;
		}
	}
	return maxLength;
}

int main()
{
	char s[] = "abcabcbb";
	int result = lengthOfLongestSubstring(s);
	printf("Length of longest substring without repeating characters: %d\n", result);
	return 0;
}