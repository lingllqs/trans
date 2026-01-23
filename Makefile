CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
CFLAGS += -std=gnu11 -Wall -Wextra -D_GNU_SOURCE

OBJS = src/main.o src/ecdict.o src/index.o

trans: $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) trans
