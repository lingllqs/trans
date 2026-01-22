#include <string.h>

#include "text.h"
#include "test.h"

int main() {
    char s1[] = "a\\nb\\nc";
    unescape_newlines(s1);
    ASSERT(strcmp(s1, "a\nb\nc") == 0);

    char s2[] = "hello world\"";
    strip_trailing_quote(s2);
    ASSERT(strcmp(s2, "hello world") == 0);

	return 0;
}
