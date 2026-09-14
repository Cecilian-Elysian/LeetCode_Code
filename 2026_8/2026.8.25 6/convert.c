#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//char* convert(char* s, int numRows) {
//	int n = strlen(s);
//	int numCols = (1 + numRows - 2) * (n / (numRows + numRows - 2));
//	int temp = n % (numRows + numRows - 2);
//	if (temp - numRows <= 0) { numCols += 1;}
//	else { numCols += 1 + (temp - numRows); }
//
//	char (*nums)[] = (char(*)[])malloc(sizeof(char) * numRows * numCols);
//	if (nums == NULL) return 1;
//
//	for (int i = 0; i < n; i++) {
//
//	}
//}



//char* convert(char* s, int numRows) {
//	int n = strlen(s);
//	int numCols = (1 + numRows - 2) * (n / (numRows + numRows - 2));
//	char* str = malloc(sizeof(char) * n);
	//int temp = 1;
	//for (int i = 0; i < n; i++) {
	//	temp += numRows - 1;
	//	if (temp <= numCols) {
	//		str[i] = s[0 + i * (numRows + 1)];
	//	}else()

	//}

//}



char* convert(char* s, int numRows) {
	
	int n = strlen(s);
	if (numRows == 1 || numRows >= n) return s;

	//int numCols = (1 + numRows - 2) * (n / (numRows + numRows - 2));

	char* str = malloc(sizeof(char) * (n + 1));
	int temp = 2 * numRows - 2;
	int count = 0;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j + i < n; j += temp) {
			str[count++] = s[j + i];
			if (0 < i && i < numRows - 1 && j + temp - i < n) {
				str[count++] = s[j + temp - i]; 
			}
		}
	}
	str[count] = '\0';
	return str;
}



int main() {
	char* s = "PAYPALISHIRING";
	int numRows = 3;
	char* result = convert(s, numRows);
	printf("%s\n", result);
	free(result);
	return 0;
}