CC = gcc
CFLAGS = -Wall -O2 -Iinclude

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

.PHONY: all clean
