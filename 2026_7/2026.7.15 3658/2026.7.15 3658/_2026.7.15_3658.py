#给你一个整数 n。请你计算以下两个值的 最大公约数（GCD）：
#• sumOdd：最小的 n 个正奇数的总和。
#• sumEven：最小的 n 个正偶数的总和。
#返回 sumOdd 和 sumEven 的 GCD。 

class Solution:
    def gcdOfOddEvenSums(self, n: int) -> int:
       if n == 0:
           return 0
       numOdd = list(range(1, 2 * n, 2))
       numEven = list(range(2, 2 * n + 1, 2))
       sumOdd = sum(numOdd)
       sumEven = sum(numEven)
       return self.gcd(sumOdd, sumEven)

    def gcd(self, a: int, b: int) -> int:
        while b:
            a, b = b, a % b
        return a

# --- 下面是本地测试的主函数 ---
if __name__ == "__main__":
    # 1. 实例化 Solution 类
    solution = Solution()
    
    # 2. 准备测试用例（可以放多个数字进去测试）
    test_cases = [3, 5, 10]
    
    # 3. 遍历测试用例并打印结果
    for n in test_cases:
        result = solution.gcdOfOddEvenSums(n)
        print(f"当 n = {n} 时，最大公约数是: {result}")