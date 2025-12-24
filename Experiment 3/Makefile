CC      = gcc
CFLAGS  = -Wall -g -O0
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
TARGET  = ./bin/DST_Set

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean