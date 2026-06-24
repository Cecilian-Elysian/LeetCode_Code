#include "bitmap.h"
#include <stdlib.h> // 引入 malloc 和 free
#include <string.h> // 引入 memset

// 定义每个字包含的位数 (32位系统通常为32)
#define BITS_PER_WORD 32
#define WORD_MASK 0x1F // 相当于 % 32

/**
 * 内部辅助函数：计算需要多少个 uint32_t 元素
 */
static size_t get_word_count(size_t bits) {
    return (bits + BITS_PER_WORD - 1) / BITS_PER_WORD;
}

// 1. 创建位图
Bitmap* bitmap_create(size_t bits) {
    if (bits == 0) return NULL;

    Bitmap *bm = (Bitmap*)malloc(sizeof(Bitmap));
    if (!bm) return NULL;

    bm->size = bits;
    size_t word_count = get_word_count(bits);
    
    // 分配内存并初始化为 0
    bm->data = (uint32_t*)calloc(word_count, sizeof(uint32_t));
    
    if (!bm->data) {
        free(bm);
        return NULL;
    }

    return bm;
}

// 2. 销毁位图
void bitmap_destroy(Bitmap *bm) {
    if (bm) {
        if (bm->data) {
            free(bm->data);
        }
        free(bm);
    }
}

// 3. 设置位 (Set Bit)
void bitmap_set(Bitmap *bm, size_t pos) {
    if (!bm || pos >= bm->size) return;

    // 计算在数组中的索引 (相当于 pos / 32)
    size_t word_idx = pos / BITS_PER_WORD;
    // 计算在字内的偏移 (相当于 pos % 32)
    uint32_t bit_offset = pos % BITS_PER_WORD;

    // 使用按位或 (|) 将特定位置为 1
    bm->data[word_idx] |= (1u << bit_offset);
}

// 4. 清除位 (Clear Bit)
void bitmap_clear(Bitmap *bm, size_t pos) {
    if (!bm || pos >= bm->size) return;

    size_t word_idx = pos / BITS_PER_WORD;
    uint32_t bit_offset = pos % BITS_PER_WORD;

    // 使用按位与 (&) 和取反 (~) 将特定位置为 0
    bm->data[word_idx] &= ~(1u << bit_offset);
}

// 5. 获取位状态 (Get Bit)
int bitmap_get(Bitmap *bm, size_t pos) {
    if (!bm || pos >= bm->size) return 0;

    size_t word_idx = pos / BITS_PER_WORD;
    uint32_t bit_offset = pos % BITS_PER_WORD;

    // 检查该位是否为 1
    return (bm->data[word_idx] & (1u << bit_offset)) != 0;
}