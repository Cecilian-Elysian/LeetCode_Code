
#include<stdio.h>

#define MAX(a, b) ( ((a) > (b)) ? a : b)

int maxScore(int* cardPoints, int cardPointsSize, int k) {
	int ans = 0;//输出值
	int count = 0;//总值
	int temp = 0;//窗口值
	for (int i = 0; i < cardPointsSize; i++) {
		count += cardPoints[i];
	}
	for (int i = 0; i < (cardPointsSize - k); i++) {
		temp += cardPoints[i];
	}
	ans = count - temp;
	for (int i = cardPointsSize - k; i < cardPointsSize; i++) {
		temp = temp - cardPoints[i + k - cardPointsSize] + cardPoints[i];
		ans = MAX(ans, (count - temp));
	}
	return ans;
}
	

int main() {
	return 0;
}