#include<stdio.h>
#include<string.h>
#define MAX(a, b) (((a) > (b)) ? a : b)

int maxVowels(char* s, int k) {
	int ans = 0;
	int count = 0;
	int Charsize = strlen(s);
	for (int i = 0; i < k; i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
			count++;
		}
	} 
	ans = MAX(ans, count);
	for (int i = k; i < Charsize; i++) {
		int left = i - k;
		if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') {
			count--;
		}
		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
			count++;
		}
		ans = MAX(ans, count);
	}
	return ans;
}

int main() {
	return 0;
}