#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void unescape_newlines(char *s) {
    char *src = s;
    char *dst = s;

    while (*src) {
        if (src[0] == '\\' && src[1] == 'n') {
            *dst++ = '\n';
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
}

static void strip_trailing_quote(char *s) {
    size_t len = strlen(s);

    if (len > 0 && s[len - 1] == '"') {
        s[len - 1] = '\0';
    }
}

/*
 * 读取一条“完整 CSV 记录”
 * 解决字段内包含换行的问题
 */
static int read_csv_record(FILE *fp, char *buf, size_t size) {
    int c;
    int in_quotes = 0;
    size_t i = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (i + 1 >= size) break;

        buf[i++] = (char)c;

        if (c == '"') in_quotes = !in_quotes;

        if (c == '\n' && !in_quotes) break;
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
static char *csv_next_field(char **cursor) {
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

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }

    const char *query = argv[1];
    FILE *fp = fopen("ecdict.csv", "r");
    if (!fp) {
        perror("open ecdict.csv");
        return 1;
    }

    char line[64 * 1024];

    /* 跳过表头 */
    read_csv_record(fp, line, sizeof(line));

    int found = 0;

    while (read_csv_record(fp, line, sizeof(line))) {
        char *cursor = line;

        char *word = csv_next_field(&cursor);
        char *phonetic = csv_next_field(&cursor);
        char *definition = csv_next_field(&cursor);
        char *translation = csv_next_field(&cursor);

        if (!word) continue;

        if (strcmp(word, query) == 0) {
            found = 1;

            printf("%s", word);
            if (phonetic && *phonetic) {
                printf(" [%s]\n\n", phonetic);
            }

            if (definition && *definition) {
                unescape_newlines(definition);
                strip_trailing_quote(definition);
                printf("EN:\n%s\n\n", definition);
            }

            if (translation && *translation) {
                unescape_newlines(translation);
                strip_trailing_quote(translation);
                printf("ZH:\n%s\n\n", translation);
            }

            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Not found: %s\n", query);
    }

    return 0;
}
