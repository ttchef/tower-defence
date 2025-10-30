
CC = gcc

CFLAGS_DEBUG = -Wall -Wextra -Werror -Wpedantic -g -O0 -fsanitize=address -fsanitize=undefined -std=c99
CFLAGS_RELEASE = -O2
CFLAGS = -Iinclude -Ivendor $(CFLAGS_DEBUG)

LDFLAGS = -lraylib -lm

DIR = ..
VENDOR = vendor

# File Dialogs
TINY_SRC = $(DIR)/$(VENDOR)/tinyfiledialogs/tinyfiledialogs.c
TINY_OBJ = $(DIR)/$(VENDOR)/tinyfiledialogs/tinyfiledialogs.o

SRC_FILES = $(shell find src -name *.c) 
OBJ_FILES = $(SRC_FILES:.c=.o) $(TINY_OBJ)

TARGET = game

all: run

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/$(TARGET): $(OBJ_FILES) $(TINY_OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TINY_OBJ): $(TINY_SRC)
	@echo "@Compiling tinzfiledialogs..."
	$(CC) -c $(TINY_SRC) -o $(TINY_OBJ)

run: clean build/$(TARGET)
	./build/$(TARGET)

clean:
	rm -rf $(OBJ_FILES) build

