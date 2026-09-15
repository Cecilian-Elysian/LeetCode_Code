#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int val;
    struct ListNode *next;
}ListNode;

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // 通过 malloc 创建头节点
    struct ListNode* headNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    headNode -> val = 0;
    headNode -> next = NULL;

    // 当前节点位头节点
    struct ListNode* current = headNode;

    int carry = 0;
    
    while(l1 != NULL || l2 != NULL || carry != 0){
        // 判断链表是否存在有值的节点
        int val1 = (l1 != NULL) ? (l1 -> val) : 0;
        int val2 = (l2 != NULL) ? (l2 -> val) : 0;
        
        // 两数相加
        int count = val1 + val2 + carry;    // 当前位相加总值
        carry = count / 10;             // 进位值
        int current_val = count % 10;       // 当前节点值
        /*
        eg:
        3 + 9 + 0 = 12 = count
        12 / 10 = 1 = carry
        12 % 10 = 2 = current_val
        */

        // 通过 malloc 创建新节点
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode -> val = current_val;
        newNode -> next = NULL;
        
        current -> next = newNode; // 将新节点链接到当前节点后面
        current = current -> next; // 将新节点作为当前节点

        if (l1 != NULL) l1 = l1 -> next;
        if (l2 != NULL) l2 = l2 -> next;
    }

    struct ListNode* result = headNode->next;
    free(headNode);
    return result;

}

// ========== 测试 ========== //

ListNode* createNode(int val) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

void printList(ListNode* head) {
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next != NULL) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

void freeList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 测试用例: 342 + 465 = 807
    // 链表表示为逆序: (2 -> 4 -> 3) + (5 -> 6 -> 4) = (7 -> 0 -> 8)
    
    // 创建链表 1: 342
    ListNode* l1 = createNode(2);
    l1->next = createNode(4);
    l1->next->next = createNode(3);

    // 创建链表 2: 465
    ListNode* l2 = createNode(5);
    l2->next = createNode(6);
    l2->next->next = createNode(4);

    printf("链表 1: ");
    printList(l1);
    printf("链表 2: ");
    printList(l2);

    // 调用两数相加函数
    ListNode* result = addTwoNumbers(l1, l2);

    printf("相加结果: ");
    printList(result); // 期望输出: 7 -> 0 -> 8

    // 释放所有分配的内存
    freeList(l1);
    freeList(l2);
    freeList(result);

    return 0;
}