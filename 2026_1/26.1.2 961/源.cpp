#include<stdio.h>



int repeatedNTimes(int* nums, int numsSize)
{
	int result = 0;
	for (int i = 0; i < numsSize - 1; i++)
	{
		for (int j = i + 1; j < numsSize; j++)
		{
			if (nums[i] == nums[j])
			{
				result = nums[i];
			}
		}
	}
	return result;
}

int main()
{
	return 0;
}