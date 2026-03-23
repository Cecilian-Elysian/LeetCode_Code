#include<stdio.h>

#define MAX(a, b) ( (a) > (b) ? a : b )

int maxVowels(char* s, int k) {
	int Vowels = 0;
	int ans = 0;
	for (int right = 0; s[right]; right++) {
		if (s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u') { Vowels++; }

		int left = right - k + 1;
		if (left < 0) { continue; }

		ans = MAX(ans, Vowels);

		char out = s[left];
		if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') { Vowels--; }
	}
	return ans;
}
int main() {
	char s[] = "abciiidef";
	int k = 3;
	printf("%d\n", maxVowels(s, k));
	return 0;
}