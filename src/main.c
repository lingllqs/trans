#include <stdio.h>
#include "ecdict.h"
#include "text.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }

    Entry e;
    if (!ecdict_lookup("data/ecdict.csv", argv[1], &e)) {
        printf("Not found: %s\n", argv[1]);
        return 0;
    }

    printf("%s", e.word);
    if (e.phonetic && *e.phonetic)
        printf(" [%s]", e.phonetic);
    printf("\n");

    if (e.definition && *e.definition) {
        strip_trailing_quote(e.definition);
        unescape_newlines(e.definition);
        printf("EN:\n%s\n\n", e.definition);
    }

    if (e.translation && *e.translation) {
        strip_trailing_quote(e.translation);
        unescape_newlines(e.translation);
        printf("ZH:\n%s\n", e.translation);
    }

    return 0;
}
