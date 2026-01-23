#include "ecdict.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "index.h"

static int g_fd;
static size_t g_size;
static const char *g_csv;
static struct index g_index;

int ecdict_open(const char *path) {
	struct stat st;

	g_fd = open(path, O_RDONLY);
	if (g_fd < 0)
		return -1;

	if (fstat(g_fd, &st) < 0)
		return -1;

	g_size = st.st_size;

	g_csv = mmap(NULL, g_size, PROT_READ, MAP_PRIVATE, g_fd, 0);
	if (g_csv == MAP_FAILED)
		return -1;

	if (index_build(&g_index, g_csv, g_size) < 0)
		return -1;

	return 0;
}

void ecdict_close(void) {
	index_free(&g_index);
	munmap((void *)g_csv, g_size);
	close(g_fd);
}

int ecdict_lookup(const char *word, const char **line) {
	const struct index_entry *e = index_lookup(&g_index, word);

	if (!e)
		return -1;

	*line = g_csv + e->offset;
	return 0;
}
