
#ifndef CSV_H
#define CSV_H

#include <stdio.h>

int read_csv_record(FILE *fp, char *buf, size_t size);
char *csv_next_field(char **cursor);

#endif // !CSV_H
