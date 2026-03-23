#include<stdio.h>
struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
	struct ListNode* prev = NULL;
	struct ListNode* curr = head;

	while (curr != NULL) {
		struct ListNode* nextTemp = curr->next; // 保存下一个
		curr->next = prev;                      // 反转
		prev = curr;                            // 前进
		curr = nextTemp;                        // 前进
	}
	return prev; // 循环结束时，prev就是新头节点
}

/*
如果输入链表是 1 -> 2 -> 3 -> NULL，函数执行过程如下：
第一轮： 处理节点 1
保存：nextTemp = 2
反转：节点 1 的 next 指向 NULL (即 prev)
移动：prev = 1, curr = 2
第二轮： 处理节点 2
保存：nextTemp = 3
反转：节点 2 的 next 指向 节点 1 (即 prev)
移动：prev = 2, curr = 3
第三轮： 处理节点 3
保存：nextTemp = NULL
反转：节点 3 的 next 指向 节点 2 (即 prev)
移动：prev = 3, curr = NULL
结束： curr 为空，退出循环，返回 prev (节点 3)。
最终结果为：3 -> 2 -> 1 -> NULL。
*/

int main() {
	struct ListNode node1 = {1, NULL};
	struct ListNode node2 = {2, NULL};
	struct ListNode node3 = {3, NULL};
	node1.next = &node2;
	node2.next = &node3;
	struct ListNode* newHead = reverseList(&node1);
	while (newHead != NULL) {
		printf("%d ", newHead->val);
		newHead = newHead->next;
	}
	return 0;
}
