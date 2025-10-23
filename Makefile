
CC = gcc

CFLAGS_DEBUG = -Wall -Wextra -Werror -Wpedantic -g -O0 -fsanitize=address -fsanitize=undefined -std=c99
CFLAGS_RELEASE = -O2
CFLAGS = -Iinclude $(CFLAGS_DEBUG)

LDFLAGS = -lraylib

SRC_FILES = $(shell find src -name *.c) 
OBJ_FILES = $(SRC_FILES:.c=.o)

all: run

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/main: $(OBJ_FILES)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: clean build/main
	./build/main

clean:
	rm -rf $(OBJ_FILES) build

