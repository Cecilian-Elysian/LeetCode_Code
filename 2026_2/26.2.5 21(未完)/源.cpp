#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};


struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
	struct ListNode sentry;						//哨兵节点
	struct ListNode* tail = &sentry;			//尾节点
	while(list1 && list2)
	{
		if (list1->val < list2->val)			//比较两个链表的头节点，哪个小就把哪个节点接到尾节点上
		{
			tail->next = list1;					//把list1的头节点接到尾节点上
			list1 = list1->next;				//把list1的头节点后移一位
		}
		else
		{
			tail->next = list2;					//把list2的头节点接到尾节点上
			list2 = list2->next;				//把list2的头节点后移一位
		}
		tail = tail->next;						//把尾节点后移一位
	}
	tail->next = list1 ? list1 : list2;			//把剩余的链表接到尾节点上
	return sentry.next;							//返回哨兵节点的下一个节点，即合并后的链表的头节点
}

int main()
{
	struct ListNode a, b, c, d, e, f;
	a.val = 1; a.next = &b;
	b.val = 2; b.next = &c;
	c.val = 4; c.next = NULL;
	d.val = 1; d.next = &e;
	e.val = 3; e.next = &f;
	f.val = 4; f.next = NULL;
	struct ListNode* head = mergeTwoLists(&a, &d);
	while(head)
	{
		printf("%d ", head->val);
		head = head->next;
	}
}
