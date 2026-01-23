#ifndef ECDICT_H
#define ECDICT_H

struct ecdict;

int ecdict_open(const char *path);
void ecdict_close(void);

int ecdict_lookup(const char *word, const char **line);

#endif
