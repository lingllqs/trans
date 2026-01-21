#include "text.h"
#include <stdio.h>
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

void strip_trailing_quote(char *s) {
    size_t len = strlen(s);

    if (len > 0 && s[len - 1] == '"') {
        s[len - 1] = '\0';
    }
}
