#include "ecdict.h"
#include <stdio.h>
#include <string.h>

/* 解析一个 CSV 字段 */
static const char *csv_field(const char *p, size_t *len) {
  const char *start;
  int quoted = 0;

  if (*p == '"') {
    quoted = 1;
    start = ++p;
  } else {
    start = p;
  }

  while (*p) {
    if (quoted) {
      if (*p == '"' && p[1] != '"')
        break;
    } else {
      if (*p == ',' || *p == '\n')
        break;
    }
    p++;
  }

  *len = p - start;
  return start;
}

/* 打印并反转义 \n */
static void print_unescaped(const char *s, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (s[i] == '\\' && i + 1 < len && s[i + 1] == 'n') {
      putchar('\n');
      i++;
    } else {
      putchar(s[i]);
    }
  }
}

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
    ecdict_close();
    return 0;
  }

  const char *p = line;
  size_t len;

  /* word */
  const char *word = csv_field(p, &len);
  printf("%.*s ", (int)len, word);
  p += len + 1;

  /* phonetic */
  const char *phon = csv_field(p, &len);
  printf("[%.*s]\n\n", (int)len, phon);
  p += len + 1;

  /* EN */
  const char *en = csv_field(p, &len);
  printf("EN:\n");
  print_unescaped(en, len);
  printf("\n\n");
  p += len + 1;

  /* ZH */
  const char *zh = csv_field(p, &len);
  printf("ZH:\n");
  print_unescaped(zh, len);
  printf("\n");

  ecdict_close();
  return 0;
}
