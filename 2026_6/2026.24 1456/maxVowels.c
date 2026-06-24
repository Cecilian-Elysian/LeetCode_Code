#include <stdio.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int maxVowels(char* s, int k) {
	int count = 0;
	int temp = 0;
	int n = strlen(s);
	for (int i = 0; i < k; i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') { temp++; }
	}
	count = MAX(count, temp);

	int left = 0;
	for (int right = k; right < n; right++, left++) {
		if (s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u') { temp++; }
		if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') { temp--; }
		count = MAX(count, temp);
	}
	return count;
}

int main() {
	char s[] = "abciiidef";
	int k = 3;
	int result = maxVowels(s, k);
	printf("Max vowels in substring of length %d: %d\n", k, result);
	return 0;
}