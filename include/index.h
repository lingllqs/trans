#ifndef INDEX_H
#define INDEX_H

#include <stddef.h>

/* 索引条目：指向 mmap 中的 word */
struct index_entry {
    size_t offset;   /* word 起始位置 */
    size_t word_len; /* word 长度 */
};

/* 索引结构 */
struct index {
    struct index_entry *entries;
    size_t count;
    const char *csv; /* mmap 基址 */
};

int index_build(struct index *idx, const char *csv, size_t size);
const struct index_entry *index_lookup(const struct index *idx, const char *word);
void index_free(struct index *idx);

#endif
