#include<stdio.h>
#include<string.h>

int maxVowels(char* s, int k) {
	int n = strlen(s);
	//字符串个数

	int left = 0, right = k - 1;
	//字符串左指针和右指针

	int Maxcount = 0;
	//最大元音字符数

	int count = 0;
	//当前窗口内最大元音字符数

	for (int i = 0; i < k; i++) {
		//初始窗口最大元音字符数

		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') { count++; }
		//判断窗口内最大元音数
	}

	Maxcount = Maxcount > count ? Maxcount : count;
	//确定最大元音字符数

	for (; right < n;) {
		//滑动窗口

		right += 1;
		//右指针向右移动

		if (s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u') { count++; }
		//新的数为元音时当前窗口内最大元音字符数加一

		if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') { count--; }
		//旧的数为元音时当前窗口内最大元音字符数减一

		left += 1;
		//左指针向右移动

		Maxcount = Maxcount > count ? Maxcount : count;
		//确定最大元音字符数
	}
	return Maxcount;
}

int main() {
	char s[] = "abciiidef";
	int k = 3;
	int result = maxVowels(s, k);
	printf("%d\n", result);
	return 0;
}