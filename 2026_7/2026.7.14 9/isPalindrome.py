class Solution:
    def isPalindrome(self, x: int) -> bool:
        s = str(x)
        return s == s[::-1]


if __name__ == "__main__":
    sol = Solution()
    # 测试用例
    test_cases = [
        (121, True),
        (-121, False),
        (10, False),
        (12321, True),
        (0, True),
        (1234, False),
    ]

    for x, expected in test_cases:
        result = sol.isPalindrome(x)
        status = "✓" if result == expected else "✗"
        print(f"{status} isPalindrome({x}) = {result} (期望: {expected})")
