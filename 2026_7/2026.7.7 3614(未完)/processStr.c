#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char processStr(char* s, long long k) {
	long long n = strlen(s);
	char* result = (char*)malloc((n + 1) * sizeof(char));
	if (!result) { return '\0'; }
	memset(result, 0, n + 1);

	long long slow = 0;

	if (n == 0) { return '\0'; }

	for (long long i = 0; s[i] != '\0'; i++) {
		if (s[i] == '*') {
			if (slow > 0) slow--;
		}

		if (s[i] == '#') {
			if (2 * slow >= n) {
				n = (n < 2 * slow) ? 2 * slow + 1 : n;
				char* new_result = (char*)realloc(result, n * sizeof(char));
				if (!new_result) {
					free(result);
					return '\0';
				}
				result = new_result;
			}

			memmove(result + slow, result, slow);
			slow *= 2;
			continue;
		}

		if (s[i] == '%') {
			for (long long j = 0; j < (slow / 2); j++) {
				char temp = result[j];
				result[j] = result[slow - j - 1];
				result[slow - j - 1] = temp;
			}
		}

		if (s[i] >= 'a' && s[i] <= 'z') {
			result[slow++] = s[i];
		}
	}
	result[slow] = '\0';

	if (slow <= k) {
		free(result);
		return '.';
	}

	char c = result[k];
	free(result);
	return c;
}

int main() {
	char s[100];
	long long k;
	scanf_s("%s %lld", s, (unsigned)sizeof(s), &k);
	char result = processStr(s, k);
	if (result == '.') {
		printf("The length of the processed string is less than k.\n");
	}
	else {
		printf("The character at index %lld is: %c\n", k, result);
	}
	return 0;
}
