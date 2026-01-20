#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../include/csv.h"
#include "../include/text.h"

/*
 * 读取一条“完整 CSV 记录”
 * 解决字段内包含换行的问题
 */

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
