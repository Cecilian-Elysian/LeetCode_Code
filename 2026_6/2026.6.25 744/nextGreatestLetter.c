#include <stdio.h>

char nextGreatestLetter(char* letters, int lettersSize, char target) {
	int left = 0, right = lettersSize - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (letters[mid] <= target) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return letters[left % lettersSize];
}

int main() {
	char letters[] = { 'c', 'f', 'j' };
	int lettersSize = sizeof(letters) / sizeof(letters[0]);
	char target = 'a';
	char result = nextGreatestLetter(letters, lettersSize, target);
	if (result != -1) {
		printf("The next greatest letter is: %c\n", letters[result]);
	}
	else {
		printf("No next greatest letter found.\n");
	}
	return 0;
}