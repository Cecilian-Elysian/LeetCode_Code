#include "hashmap.h"
#include <stdlib.h>
#include <stdio.h>

// === 私有定义 (仅本文件可见) ===

// 1. 定义链表节点 (私有结构)
typedef struct Node {
	int key;// 键
	int value;// 值
    struct Node* next;
} Node;

// 2. 定义哈希表实际结构 (私有结构)
// 这里定义了 HashMap 的真实内容，与头文件中的声明对应
struct HashMap {
    int size;        // 桶的数量
    int count;       // 当前元素数量 (用于统计)
    Node** buckets;  // 桶数组
};

// 3. 私有函数声明 (仅本文件使用，对外不可见)
// 哈希函数
static int hash(int key, int size) {
    return abs(key) % size;
}

// === 公有函数实现 ===

HashMap* hashmap_create(int size) {
    if (size <= 0) return NULL;

    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->size = size;
    map->count = 0;
    // 分配桶内存，初始化为 0
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    return map;
}

void hashmap_destroy(HashMap* map) {
    if (!map) return;

    // 释放所有链表节点
    for (int i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    // 释放桶数组和结构体本身
    free(map->buckets);
    free(map);
}

void hashmap_put(HashMap* map, int key, int value) {
    if (!map) return;

    int index = hash(key, map->size);
    Node* head = map->buckets[index];

    // 检查键是否已存在，存在则更新
    Node* current = head;
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // 键不存在，头插法插入新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return; // 内存分配失败处理

    newNode->key = key;
    newNode->value = value;
    newNode->next = head; // 指向原来的头节点
    map->buckets[index] = newNode; // 桶指向新节点
    map->count++;
}

int hashmap_get(HashMap* map, int key) {
    if (!map) return -1;

    int index = hash(key, map->size);
    Node* current = map->buckets[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return -1; // 未找到
}

void hashmap_remove(HashMap* map, int key) {
    if (!map) return;

    int index = hash(key, map->size);
    Node* head = map->buckets[index];

    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                // 删除的是头节点
                map->buckets[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            map->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int hashmap_size(HashMap* map) {
    return map ? map->count : 0;
}