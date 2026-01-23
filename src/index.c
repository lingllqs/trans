#include "index.h"

#include <stdlib.h>
#include <string.h>

/* mmap 的 csv 基址，供比较函数使用 */
static const char *g_csv;

/* 索引排序用比较函数 */
static int index_entry_cmp(const void *a, const void *b)
{
    const struct index_entry *ea = a;
    const struct index_entry *eb = b;

    const char *wa = g_csv + ea->offset;
    const char *wb = g_csv + eb->offset;

    size_t min = ea->word_len < eb->word_len ? ea->word_len : eb->word_len;

    int r = memcmp(wa, wb, min);
    if (r != 0)
        return r;

    return (int)ea->word_len - (int)eb->word_len;
}

/* bsearch：key vs entry */
static int index_word_cmp(const void *key, const void *elem)
{
    const char *word = key;
    const struct index_entry *e = elem;

    size_t key_len = strlen(word);
    size_t min = key_len < e->word_len ? key_len : e->word_len;

    int r = memcmp(word, g_csv + e->offset, min);
    if (r != 0)
        return r;

    return (int)key_len - (int)e->word_len;
}

int index_build(struct index *idx, const char *csv, size_t size)
{
    size_t capacity = 1024;
    size_t count = 0;

    struct index_entry *entries = malloc(capacity * sizeof(*entries));
    if (!entries)
        return -1;

    g_csv = csv;

    for (size_t i = 0; i < size;) {
        // 当前word起始位置
        size_t start = i;

        /* 找到 word 结尾（逗号） */
        while (i < size && csv[i] != ',')
            i++;

        if (i == size)
            break;

        if (count == capacity) {
            capacity *= 2;
            entries = realloc(entries, capacity * sizeof(*entries));
            if (!entries)
                return -1;
        }

        entries[count].offset = start;
        entries[count].word_len = i - start;
        count++;

        /* 跳到下一行 */
        while (i < size && csv[i] != '\n')
            i++;
        i++;
    }

    // 排序
    qsort(entries, count, sizeof(*entries), index_entry_cmp);

    idx->entries = entries;
    idx->count = count;
    idx->csv = csv;
    return 0;
}

const struct index_entry *index_lookup(const struct index *idx, const char *word)
{
    return bsearch(word, idx->entries, idx->count, sizeof(struct index_entry), index_word_cmp);
}

void index_free(struct index *idx)
{
    free(idx->entries);
    idx->entries = NULL;
    idx->count = 0;
}
