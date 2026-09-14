from typing import List

# class Solution:
#     def twoSum(self, nums: List[int], target: int) -> List[int]:
#         for i in range(len(nums)):
#             for j in range(i + 1, len(nums)):
#                 if nums[i] + nums[j] == target:
#                     return[i, j]
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        seen: dict[int, int] = {}
        for i, num in enumerate(nums):
            count = target - num
            if count in seen:
                return [seen[count], i]
            seen[num] = i  
        return []


# 程序的执行入口,只有当我被直接运行时，才执行下面的代码
if __name__ == "__main__":
    # 1. 准备测试数据
    test_nums = [2, 7, 11, 15]
    test_target = 9
    
    # 2. 实例化类并调用方法
    solution = Solution()
    result = solution.twoSum(nums=test_nums, target=test_target)
    
    # 3. 打印输出结果
    print(f"输入数组: {test_nums}")
    print(f"目标值: {test_target}")
    print(f"结果索引: {result}")


# nums_list = [1, 2, 3] 列表 list → []
# nums_tuple = (1, 2, 3) 元组 tuple  → ()
# nums_dict = {"a": 1} 字典 dict    → {}
# nums_set    = {1, 2, 3} 集合 set     → {}                