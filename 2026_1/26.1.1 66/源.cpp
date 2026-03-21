#include<stdio.h>
#include<stdlib.h>

int function(int base, int exp)
{
	int result = 1;
	for (int i = 0; i < exp; i++)
	{
		result = result * base;
	}
	return result;
}


int* plusOne(int* digits, int digitsSize, int* returnSize) 
{
    int one = 1;
    int n = digitsSize;
    int* result = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = n - 1; i >= 0; i--) 
    {
        int sum = digits[i] + one;
        result[i + 1] = sum % 10;
        one = sum / 10;
    }

    if (one)
    {
        result[0] = 1;
        *returnSize = n + 1;
        return result;
    }
    else 
    {
        *returnSize = n;
        return result + 1;
    }
}


int main() {
    int digits[] = { 1, 9, 9, 9 };
    int size = sizeof(digits) / sizeof(digits[0]);
    int returnSize;

    int* result = plusOne(digits, size, &returnSize);

    printf("Result: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // 注意：如果结果有进位，result 指向 malloc 的数组开头；否则指向中间
    // 为了安全释放，我们记录原始指针
    int* original = result;
    if (returnSize == size) {
        original--; // 回退到 malloc 的起始位置
    }
    free(original);

    return 0;
}