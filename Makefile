
CC = gcc

# Debug Flags
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g -O0 -fsanitize=address -fsanitize=undefined

# Release Flags 
CFLAGS = -O2

LDFLAGS = 

SRC_FILES = $(wildcard src/*.c) 
OBJ_FILES = $(SRC_FILES:.c=.o)

all: build/main

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/main: $(OBJ_FILES)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./build/main

clean:
	rm -rf $(OBJ_FILES) build

