#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "test.h"
#include "text.h"

int main() {
    char buf[1024];
    char input[] = "word,phonetic,definition,translation\n"
                   "\"how\",\"hau\",\"a\\nb\",\"c,d\"\n";

	FILE *fp = fmemopen(input, sizeof(input), "r");
	ASSERT(fp);

	ASSERT(csv_read_record(fp, buf, sizeof(buf))); // 跳过第一行
	ASSERT(csv_read_record(fp, buf, sizeof(buf)));

	char *cur = buf;
	char *w = csv_next_field(&cur);
	char *p = csv_next_field(&cur);
	char *d = csv_next_field(&cur);
	char *t = csv_next_field(&cur);

	strip_trailing_quote(w);
	strip_trailing_quote(p);
	strip_trailing_quote(d);
	strip_trailing_quote(t);

	ASSERT(strcmp(w, "how") == 0);
	ASSERT(strcmp(p, "hau") == 0);
	ASSERT(strcmp(d, "a\\nb") == 0);
	ASSERT(strcmp(t, "c,d") == 0);

	fclose(fp);

    return 0;
}
