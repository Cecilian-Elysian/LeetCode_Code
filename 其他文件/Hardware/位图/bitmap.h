#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h> // 引入标准整数类型
#include <stddef.h> // 引入 size_t 类型

// 定义位图结构体
typedef struct {
    uint32_t *data;  // 存储位图数据的数组（使用32位无符号整数）
    size_t size;     // 位图的最大位数（容量）
} Bitmap;

/**
 * 创建位图
 * @param bits 需要管理的最大位数
 * @return 指向 Bitmap 结构体的指针，失败返回 NULL
 */
Bitmap* bitmap_create(size_t bits);

/**
 * 销毁位图（释放内存）
 * @param bm 位图指针
 */
void bitmap_destroy(Bitmap *bm);

/**
 * 设置指定位为 1 (标记存在)
 * @param bm 位图指针
 * @param pos 位置索引 (从 0 开始)
 */
void bitmap_set(Bitmap *bm, size_t pos);

/**
 * 清除指定位为 0 (标记不存在)
 * @param bm 位图指针
 * @param pos 位置索引
 */
void bitmap_clear(Bitmap *bm, size_t pos);

/**
 * 获取指定位的状态
 * @param bm 位图指针
 * @param pos 位置索引
 * @return 1 表示存在，0 表示不存在
 */
int bitmap_get(Bitmap *bm, size_t pos);

#endif // BITMAP_H