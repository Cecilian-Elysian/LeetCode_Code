#include "hashmap.h"
#include <stdio.h>

int main() {
    // 1. 创建哈希表
    HashMap* myMap = hashmap_create(10);
    if (!myMap) {
        printf("创建失败!\n");
        return -1;
    }

    // 2. 存入数据
    hashmap_put(myMap, 1, 100);
    hashmap_put(myMap, 2, 200);

    // 模拟冲突: 12 和 2 的哈希值相同 (2 % 10 = 2, 12 % 10 = 2)
    hashmap_put(myMap, 12, 999);

    // 3. 读取数据
    printf("Key 1: %d\n", hashmap_get(myMap, 1));   // 100
    printf("Key 2: %d\n", hashmap_get(myMap, 2));   // 200
    printf("Key 12: %d\n", hashmap_get(myMap, 12)); // 999

    // 4. 更新数据
    hashmap_put(myMap, 2, 888);
    printf("更新后 Key 2: %d\n", hashmap_get(myMap, 2)); // 888

    // 5. 删除数据
    hashmap_remove(myMap, 12);
    printf("删除后 Key 12: %d\n", hashmap_get(myMap, 12)); // -1

    // 6. 打印大小
    printf("当前元素个数: %d\n", hashmap_size(myMap)); // 2

    // 7. 释放资源
    hashmap_destroy(myMap);

    return 0;
}