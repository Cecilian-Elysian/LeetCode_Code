#include <stdio.h>

int removeElement(int* nums, int numsSize, int val) {
    if (numsSize == 0) return 0;
    int slow = 0; 
    for (int fast = 0; fast < numsSize; fast++) { 
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow; 
}

int main() {
    int nums[] = { 3, 2, 2, 3 };
    int val = 3;
    int newLength = removeElement(nums, sizeof(nums) / sizeof(nums[0]), val);
    printf("New length: %d\n", newLength);
    printf("Modified array: ");
    for (int i = 0; i < newLength; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}
