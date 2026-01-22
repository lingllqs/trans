CC = gcc
CFLAGS = -Wall -O2 -Iinclude -Itests

SRC = \
    src/main.c \
    src/csv.c \
    src/text.c \
    src/ecdict.c

OBJ = $(SRC:.c=.o)

TARGET = trans

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

TESTS = \
    tests/test_csv \
    tests/test_text \
    tests/test_ecdict

tests/%: tests/%.c src/csv.c src/text.c src/ecdict.c
	$(CC) $(CFLAGS) -Iinclude -o $@ $^

test: $(TESTS)
	@for t in $(TESTS); do \
	    echo "Running $$t"; \
	    ./$$t; \
	done
	@echo "All tests passed"

.PHONY: all clean test
