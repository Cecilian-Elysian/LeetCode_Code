#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int strStr(char* haystack, char* needle) {
	int c1 = strlen(haystack);
	int c2 = strlen(needle);
	if (c1 < c2)return -1;
	char* temp = (char*)malloc(sizeof(char) * c2);
	for (int i = 0; i < c2; i++) {
		temp[i] = haystack[i];
	}
	int left = 0;
	for (int i = c2;c2 < c1; i++){
		if (strcmp(temp, needle) == 0)return left;
		temp[left] = haystack[i];
		left++;
	}
	if (strcmp(temp, needle) == 0)return left;
	return -1;
}