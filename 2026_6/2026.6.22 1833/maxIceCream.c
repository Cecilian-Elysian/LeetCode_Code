#include <stdio.h>
#include <stdlib.h>
//计数排序
int maxIceCream(int* costs, int costsSize, int coins) {
	//找到最大值和最小值
	int max = costs[0], min = costs[0];
	for (int i = 0; i < costsSize; i++) {
		if (costs[i] > max) { max = costs[i]; }
		if (costs[i] < min) { min = costs[i]; }
	}
	int range = max - min + 1;
	//统计频率
	int* count = (int*)calloc(range, sizeof(int));
	for (int i = 0; i < costsSize; i++) {
		count[costs[i] - min]++;
	}

	int total = 0;
	for (int p = 0; p < range; p++) {
		if (count[p] == 0) continue; // 这个价格的雪糕不存在，跳过

		int price = p + min;         // 还原真实价格
		if (coins < price) break;    // 连最便宜的都买不起了，直接结束

		// 计算当前价格最多能买多少个
		int can_buy = coins / price;
		if (can_buy > count[p]) can_buy = count[p]; // 不能超过库存

		total += can_buy;
		coins -= can_buy * price;
	}

	free(count);
	return total;
}

int main() {
	int costs[] = { 1, 3, 2, 4, 1 };
	int coins = 7;
	int result = maxIceCream(costs, sizeof(costs) / sizeof(costs[0]), coins);
	printf("Maximum ice cream bars: %d\n", result);
	return 0;
}