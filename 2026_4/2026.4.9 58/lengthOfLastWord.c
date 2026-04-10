#include<stdio.h>
#include<string.h>

int lengthOfLastWord(char* s);

int main() {
    char s[] = "Hello World";
    int result = lengthOfLastWord(s);
    printf("Length of the last word: %d\n", result);
	return 0;
}


int lengthOfLastWord(char* s) {
    int n = strlen(s);
    int count = 0;
    int left = 0;
    int right = n - 1;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
    int i = 0;
    while (i < n && s[i] == ' ') { i++; }
    while (i < n && s[i] != ' ') {
        count++;
        i++;
    }
    return count;
}