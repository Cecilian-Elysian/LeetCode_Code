#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(char* n) {
	int len = strlen(n);
	int count[26] = { 0 };
	for (int i = 0; i < len; i++) {
		count[n[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {
		if (count[i] > 0) {
			return count[i];
		}
	}
	return 0;
}

int* numSmallerByFrequency(char** queries, int queriesSize, char** words, int wordsSize, int* returnSize) {
    int* answer = (int*)malloc(sizeof(int) * queriesSize);
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int count = 0;
        for (int j = 0; j < wordsSize; j++) {
            
            if (f(queries[i]) < f(words[j])) { 
                count++;
            }
        }
        answer[i] = count;
    }
    return answer;
}

int main() {
	char* queries[] = { "cbd" };
	char* words[] = { "zaaaz" };
	int returnSize;
	int* result = numSmallerByFrequency(queries, 1, words, 1, &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%d ", result[i]);
	}
	free(result);
	return 0;
}