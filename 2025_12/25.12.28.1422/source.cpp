#include<stdio.h>
#include<string.h>

int maxScore(char* s) {
    int len = strlen(s);
    int totalOnes = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '1') totalOnes++;
    }
    int best = 0;
    int leftZeros = 0;
    int leftOnes = 0;
    for (int i = 0; i < len - 1; i++) {
        if (s[i] == '0') leftZeros++;
        else leftOnes++;
        int score = leftZeros + (totalOnes - leftOnes);
        if (score > best) best = score;
    }
    return best;
}

int main() {
    char s[] = "011101";
    printf("%d\n", maxScore(s));
    return 0;
}
