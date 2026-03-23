#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
	struct ListNode* curr = head;			//将curr节点设置为头节点
	struct ListNode* prev = NULL;			//将prev节点设置为空
	while (curr)
	{
		struct ListNode* next = curr->next;	//将next节点设置为下一个节点
		curr->next = prev;					//使next节点指向前一个节点
		prev = curr;						//将prev节点变为当前节点
		curr = next;						//将curr节点变为下一个节点
	}
	return prev;
}

