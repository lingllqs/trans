#include "../include/csv.h"

int read_csv_record(FILE *fp, char *buf, size_t size) {
    int c;
    int in_quotes = 0;
    size_t i = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (i + 1 >= size) {
            break;
        }

        buf[i++] = (char)c;

        if (c == '"') {
            in_quotes = !in_quotes;
        }

        if (c == '\n' && !in_quotes) {
            break;
        }
    }

    buf[i] = '\0';
    return (i > 0);
}

/*
 * 读取下一个 CSV 字段（就地解析）
 * 支持：
 *   - 双引号
 *   - 字段内逗号
 *   - 字段内换行
 */
char *csv_next_field(char **cursor) {
    char *p = *cursor;
    char *start;
    int in_quotes = 0;

    if (!p || *p == '\0') return NULL;

    /* 跳过起始引号 */
    if (*p == '"') {
        in_quotes = 1;
        p++;
    }

    start = p;

    while (*p) {
        if (in_quotes) {
            if (*p == '"' && *(p + 1) != '"') {
                in_quotes = 0;
            }
        } else {
            if (*p == ',' || *p == '\n') break;
        }
        p++;
    }

    /* 截断字段 */
    if (*p) {
        *p = '\0';
        p++;
    }

    *cursor = p;
    return start;
}
