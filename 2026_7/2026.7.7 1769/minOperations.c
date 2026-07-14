#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int* minOperations(char* boxes, int* returnSize) {
    int temp = 0;
    int n = strlen(boxes);

	int* answer = (int*)malloc(sizeof(int) * n);

    if (answer == NULL) { 
        *returnSize = 0;
        return NULL;
    }

	for (int i = 0; i < n; i++) {
        temp = 0;
		for (int j = 0; j < n; j++) {
			if (boxes[j] == '0') { continue; }
			temp += abs(j - i);
		}
		answer[i] = temp;
	}
    *returnSize = n;
	return answer;
}

int main() {
    // 测试用例
    char boxes[] = "110";
    int returnSize = 0;

    // 调用函数
    int* result = minOperations(boxes, &returnSize);

    // 打印结果
    printf("输入: \"%s\"\n", boxes);
    printf("输出: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) printf(", ");
    }
    printf("]\n");

    // 【重要】释放函数内部 malloc 分配的内存
    free(result);

    return 0;
}