#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void reverse(char* s) {
	int len = strlen(s);
	for (int i = 0; i < len / 2; i++) {
		char temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
	}
}


char* addBinary(char* a, char* b) {
	int len_a = strlen(a);
	int len_b = strlen(b);
	int carry = 0;
	int max_len = (len_a > len_b ? len_a : len_b) + 2;

	char* result = (char*)malloc(max_len * sizeof(char));
	if (result == NULL) return NULL;
	int index_a = len_a - 1;//字符串a的最后一个字符的索引
	int index_b = len_b - 1;//字符串b的最后一个字符的索引
	int index_result = 0; // 必须初始化为 0
	while (index_a >= 0 || index_b >= 0 || carry > 0) {
		int sum = carry;

		if (index_a >= 0) {
			sum += (a[index_a] - '0');
			index_a--;
		}

		if (index_b >= 0) {
			sum += (b[index_b] - '0');
			index_b--;
		}

		result[index_result] = (sum % 2) + '0';
		carry = sum / 2;//计算进位
		index_result++;

	}

	result[index_result] = '\0';//添加字符串结束符
	reverse(result);//反转结果字符串
	return result;
}

int main() {
	char a[] = "1010";
	char b[] = "1011";
	char* result = addBinary(a, b);
	printf("Result: %s\n", result);
	free(result);
	return 0;
}