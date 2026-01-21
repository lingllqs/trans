#ifndef ECDICT_H
#define ECDICT_H

typedef struct {
	char *word;
	char *phonetic;
	char *definition;
	char *translation;
} Entry;

int ecdict_lookup(const char *path, const char *query, Entry *out);

#endif // !ECDICT_H
