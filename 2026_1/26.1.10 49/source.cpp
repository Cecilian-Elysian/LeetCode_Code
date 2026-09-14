#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of groups where each group contains strings that are
 * anagrams of each other. The returned array and the strings inside must
 * be malloced by the caller (we malloc one large block per group for
 * simplicity).
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize,
                     int** returnColumnSizes) {
    int n = strsSize;
    int* used = (int*)calloc(n, sizeof(int));
    char*** groups = (char***)malloc(n * sizeof(char**));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    int groupCount = 0;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = 1;
        int len = strlen(strs[i]);
        int* baseCount = (int*)calloc(26, sizeof(int));
        for (int k = 0; k < len; k++) baseCount[strs[i][k] - 'a']++;

        int groupCap = 4;
        char** group = (char**)malloc(groupCap * sizeof(char*));
        group[0] = strs[i];
        int groupSize = 1;

        for (int j = i + 1; j < n; j++) {
            if (used[j]) continue;
            int jlen = strlen(strs[j]);
            if (jlen != len) continue;
            int* c = (int*)calloc(26, sizeof(int));
            for (int k = 0; k < jlen; k++) c[strs[j][k] - 'a']++;
            int match = 1;
            for (int k = 0; k < 26; k++) {
                if (c[k] != baseCount[k]) { match = 0; break; }
            }
            free(c);
            if (match) {
                if (groupSize >= groupCap) {
                    groupCap *= 2;
                    group = (char**)realloc(group, groupCap * sizeof(char*));
                }
                group[groupSize++] = strs[j];
                used[j] = 1;
            }
        }
        free(baseCount);
        groups[groupCount] = group;
        (*returnColumnSizes)[groupCount] = groupSize;
        groupCount++;
    }
    free(used);
    *returnSize = groupCount;
    return groups;
}

int main() {
    char s0[] = "eat";
    char s1[] = "tea";
    char s2[] = "tan";
    char s3[] = "ate";
    char s4[] = "nat";
    char s5[] = "bat";
    char* strs[] = { s0, s1, s2, s3, s4, s5 };
    int returnSize;
    int* returnColumnSizes;
    char*** result = groupAnagrams(strs, 6, &returnSize, &returnColumnSizes);
    printf("%d groups\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%s%s", j > 0 ? "," : "", result[i][j]);
        }
        printf("]\n");
    }
    return 0;
}
