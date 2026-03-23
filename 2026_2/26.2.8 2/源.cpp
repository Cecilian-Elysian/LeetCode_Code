#include<stdio.h>
#include<stdlib.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

/*
*  l1 = [9, 9] 
*  l2 = [1]
*/
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode* head = NULL, * tail = NULL;
	int carry = 0;
	while (l1 || l2 || carry){
		int sum = carry;
		if (l1) {
			sum = sum + l1->val;
			l1 = l1->next;
		}
		if (l2) {
			sum = sum + l2->val;
			l2 = l2->next;
		}
		carry = sum / 10;
		sum = sum % 10;
		struct ListNode* Node = (struct ListNode*)malloc(sizeof(struct ListNode));
		Node->val = sum;
		Node->next = NULL;

		if (!head) {
			head = tail = Node;
		}
		else {
			tail->next = Node;
			tail = Node;
		}
	}
	return head;
}

int main() {
	struct ListNode* l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
	l1->val = 9;
	l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
	l1->next->val = 9;
	l1->next->next = NULL;
	struct ListNode* l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
	l2->val = 1;
	l2->next = NULL;
	struct ListNode* result = addTwoNumbers(l1, l2);
	while (result) {
		printf("%d ", result->val);
		result = result->next;
	}
	return 0;
}