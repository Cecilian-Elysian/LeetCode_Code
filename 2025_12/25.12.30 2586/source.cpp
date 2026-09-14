#include<stdio.h>
#include<string.h>

int vowelStrings(char** words, int wordsSize, int left, int right) {
    int count = 0;
    for (int i = left; i <= right && i < wordsSize; i++) {
        int m = strlen(words[i]);
        if (m == 0) continue;
        char first = words[i][0];
        char last = words[i][m - 1];
        int isVowel = (first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u');
        if (isVowel) {
            isVowel = (last == 'a' || last == 'e' || last == 'i' || last == 'o' || last == 'u');
            if (isVowel) count++;
        }
    }
    return count;
}

int main() {
    char w0[] = "are";
    char w1[] = "amy";
    char w2[] = "u";
    char w3[] = "apple";
    char w4[] = "echo";
    char* words[] = { w0, w1, w2, w3, w4 };
    printf("%d\n", vowelStrings(words, 5, 0, 4));
    return 0;
}
