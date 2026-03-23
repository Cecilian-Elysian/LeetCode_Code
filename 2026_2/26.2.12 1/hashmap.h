#ifndef HASHMAP_H
#define HASHMAP_H

// 不透明指针 (Opaque Pointer)
// 外部使用者只知道有一个 HashMap 类型，但不知道它内部具体长什么样
typedef struct HashMap HashMap;

// --- 接口函数声明 ---

// 创建哈希表
// 参数: size - 桶的数量
// 返回: 指向新创建的哈希表的指针
HashMap* hashmap_create(int size);

// 销毁哈希表 (会释放所有内存)
void hashmap_destroy(HashMap* map);

// 插入或更新键值对
// 参数: map - 哈希表指针, key - 键, value - 值
void hashmap_put(HashMap* map, int key, int value);

// 查找值
// 参数: map - 哈希表指针, key - 键
// 返回: 如果找到返回对应的值，否则返回 -1 (业务逻辑约定)
int hashmap_get(HashMap* map, int key);

// 删除键值对
void hashmap_remove(HashMap* map, int key);

// 获取元素数量 (可选接口)
int hashmap_size(HashMap* map);

#endif // HASHMAP_H
