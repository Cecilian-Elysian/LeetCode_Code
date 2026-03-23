#include<stdio.h>
#include<string.h>

/*给你一个长度为 n 下标从 0 开始的字符串 blocks ，
blocks[i] 要么是 'W' 要么是 'B' ，表示第 i 块的颜色。
字符 'W' 和 'B' 分别表示白色和黑色。
给你一个整数 k ，表示想要 连续 黑色块的数目。 
每一次操作中，你可以选择一个白色块将它 涂成 黑色块。
请你返回至少出现 一次 连续 k 个黑色块的 最少 操作次数。  */

#define MIN(a, b) ( ((a) > (b)) ? b : a )

int minimumRecolors(char* blocks, int k) {
	
	int n = strlen(blocks);
	int count = 0;
	int ans = 0;

	for (int right = 0; right < k; right++) {
		if (blocks[right] == 'W') { count++; }
	}
	ans = count;
	for (int right = k; right < n; right++) {
		int left = right - k;

		if (blocks[right] == 'W') { count++; }
		if (blocks[left] == 'W') { count--; }
		ans = MIN(ans, count);
	}
	return ans;
}

int main() {
    // --- 测试用例 1 ---
    // 字符串: W B B W W B B W B W
    // 索引:   0 1 2 3 4 5 6 7 8 9
    // 寻找长度为 7 的子串，最少的 'W' 数量
    // 最优解是子串 [3,9]: "WBBWBW" 或者 [1,7]: "BBWWBB" 实际上最少是 3 个 W
    char blocks1[] = "WBBWWBBWBW";
    int k1 = 7;
    int result1 = minimumRecolors(blocks1, k1);
    printf("测试 1: blocks = \"%s\", k = %d\n", blocks1, k1);
    printf("最少需要操作次数: %d\n\n", result1);

    // --- 测试用例 2 ---
    // 字符串: W B W W
    // 如果 k=2, 可能的子串: "WB"(1个W), "BW"(1个W), "WW"(2个W)
    // 最少只需要改 1 次
    char blocks2[] = "WBWW";
    int k2 = 2;
    int result2 = minimumRecolors(blocks2, k2);
    printf("测试 2: blocks = \"%s\", k = %d\n", blocks2, k2);
    printf("最少需要操作次数: %d\n\n", result2);

    // --- 测试用例 3 ---
    // 字符串全是黑色，不需要操作
    char blocks3[] = "BBBBB";
    int k3 = 3;
    int result3 = minimumRecolors(blocks3, k3);
    printf("测试 3: blocks = \"%s\", k = %d\n", blocks3, k3);
    printf("最少需要操作次数: %d\n", result3);

    return 0;
}