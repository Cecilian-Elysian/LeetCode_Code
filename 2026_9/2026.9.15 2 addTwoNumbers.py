from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        head = ListNode(0)
        current = head
        carry = 0 #进位

        while l1 is not None or l2 is not None or carry:
            # 三元判断符
            # A if 条件 else B 
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            
            total = val1 + val2 + carry     # 当前位求和
            carry = total // 10             # 整除计算新进位
            current_val = total % 10        # 取出当前位的结果

            # 接入新节点
            current.next = ListNode(current_val)
            current = current.next

            # 移动指针
            if l1:
                l1 = l1.next
            if l2:
                l2 = l2.next

        return head.next

# ========== 测试代码 ========== #

# 辅助函数：将列表转为链表（头节点为第一个元素）
def list_to_linked_list(lst: List[int]) -> Optional[ListNode]:
    if not lst:
        return None
    head = ListNode(lst[0])
    current = head
    for val in lst[1:]:
        current.next = ListNode(val)
        current = current.next
    return head

# 辅助函数：将链表转为列表（方便打印结果）
def linked_list_to_list(head: Optional[ListNode]) -> List[int]:
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

if __name__ == "__main__":
    solution = Solution()

     # 测试用例 1：普通情况
    # 342 + 465 = 807
    l1 = list_to_linked_list([2, 4, 3])
    l2 = list_to_linked_list([5, 6, 4])
    result = solution.addTwoNumbers(l1, l2)
    print("测试1:", linked_list_to_list(result))  # 预期输出: [7, 0, 8]
    
    # 测试用例 2：包含 0 的情况
    # 0 + 0 = 0
    l1 = list_to_linked_list([0])
    l2 = list_to_linked_list([0])
    result = solution.addTwoNumbers(l1, l2)
    print("测试2:", linked_list_to_list(result))  # 预期输出: [0]
    
    # 测试用例 3：链表长度不同且有进位
    # 9999999 + 9999 = 10009998
    l1 = list_to_linked_list([9, 9, 9, 9, 9, 9, 9])
    l2 = list_to_linked_list([9, 9, 9, 9])
    result = solution.addTwoNumbers(l1, l2)
    print("测试3:", linked_list_to_list(result))  # 预期输出: [8, 9, 9, 9, 0, 0, 0, 1]
