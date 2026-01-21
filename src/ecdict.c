#include "ecdict.h"
#include "csv.h"
#include <stdio.h>
#include <string.h>

int ecdict_lookup(const char *path, const char *query, Entry *out) {
    FILE *fp = fopen(path, "r");
    if (!fp)
        return 0;

    char line[64 * 1024];

    /* 跳过表头 */
    csv_read_record(fp, line, sizeof(line));

    while (csv_read_record(fp, line, sizeof(line))) {
        char *cursor = line;

        char *word        = csv_next_field(&cursor);
        char *phonetic    = csv_next_field(&cursor);
        char *definition  = csv_next_field(&cursor);
        char *translation = csv_next_field(&cursor);

        if (!word)
            continue;

        if (strcmp(word, query) == 0) {
            out->word        = word;
            out->phonetic    = phonetic;
            out->definition  = definition;
            out->translation = translation;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
