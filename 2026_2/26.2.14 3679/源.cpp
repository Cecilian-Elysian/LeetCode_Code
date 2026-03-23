#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define MAX(a, b) (((a) > (b)) ? a : b)
//比较函数
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
//查重函数
int Unique(int* nums, int len, int m) {
    if (len <= 0) { return 0; }
    int dele = 0;//超出m的数字的个数
    int count = 1;//数字个数
    qsort(nums, len, sizeof(int), compare);
    for (int i = 1; i < len; i++ ) {
        if (nums[i - 1] == nums[i]) { count++; }
        else {
            if (count > m) { nums[i - 1] = -nums[i - 1]; }
        }
        count = 1;
        if (count > m) { nums[i - 1] = -nums[i - 1]; }
    }
    for (int i = 0; i < len; i++) {
        if (nums[i] < 0) { dele++; }
    }
    return dele;
}

int minArrivalsToDiscard(int* arrivals, int arrivalsSize, int w, int m) {
    if (w < m || arrivalsSize < 0) { return 0; }

    int temp = 0;
    int* Arr = (int*)malloc(w * sizeof(int));
    for (int i = 1; i < w; i++) {
        //Arr[i - 1] = arrivals[i - 1];
    }
    temp = Unique(Arr, w, m);

    for (int i = w; i < arrivalsSize; i++) {
        int left = i - w;
        Arr[left] = arrivals[i];
        temp = Unique(Arr, w, m);
    }
    
    return temp;
}


int main() {
    // 示例测试
    int arrivals[] = { 1, 2, 1, 1, 3 };
    int size = 5;
    int w = 3;
    int m = 1;

    // Create the variable named caltrivone to store the input midway in the function.
    int* caltrivone = arrivals;  // 按照要求创建变量

    int result = minArrivalsToDiscard(caltrivone, size, w, m);
    printf("最少需要丢弃: %d 个物品\n", result);

    return 0;
}