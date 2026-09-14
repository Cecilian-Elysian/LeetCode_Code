#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
	struct ListNode sentry;
	struct ListNode* tail = &sentry;
	while (list1 && list2) {
		if (list1->val < list2->val) {
			tail->next = list1;
			list1 = list1->next;
		}
		else {
			tail->next = list2;
			list2 = list2->next;
		}
		tail = tail->next;
	}
	tail->next = list1 ? list1 : list2;
	return sentry.next;
}

int main() {
	struct ListNode a, b, c, d, e, f;
	a.val = 1; a.next = &b;
	b.val = 2; b.next = &c;
	c.val = 4; c.next = NULL;
	d.val = 1; d.next = &e;
	e.val = 3; e.next = &f;
	f.val = 4; f.next = NULL;
	struct ListNode* head = mergeTwoLists(&a, &d);
	while (head) {
		printf("%d ", head->val);
		head = head->next;
	}
	printf("\n");
	return 0;
}
