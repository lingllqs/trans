#include <stdio.h>

#include "ecdict.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s WORD\n", argv[0]);
        return 1;
    }

    if (ecdict_open("data/ecdict.csv") < 0) {
        fprintf(stderr, "failed to open dictionary\n");
        return 1;
    }

    const char *line;
    if (ecdict_lookup(argv[1], &line) < 0) {
        printf("not found\n");
    } else {
        const char *p = line;
        while (*p && *p != '\n') putchar(*p++);
        putchar('\n');
    }

    ecdict_close();
    return 0;
}
