
CC = gcc

DIR = ..
VENDOR = $(DIR)/vendor

CFLAGS_DEBUG = -Wall -Wextra -Werror -Wpedantic -g -O0 -fsanitize=address -fsanitize=undefined -std=c99
CFLAGS_RELEASE = -O2
CFLAGS = -Iinclude -I$(VENDOR) $(CFLAGS_DEBUG)

LDFLAGS = -lraylib -lm

# File Dialogs
TINY_SRC = $(VENDOR)/tinyfiledialogs/tinyfiledialogs.c
TINY_OBJ = $(VENDOR)/tinyfiledialogs/tinyfiledialogs.o

# Json parsing
WSJSON_SRC = $(VENDOR)/wsJson/src/ws_json.c
WSJSON_OBJ = $(VENDOR)/wsJson/src/ws_json.o

SRC_FILES = $(shell find src -name *.c) 
OBJ_FILES = $(SRC_FILES:.c=.o) $(TINY_OBJ) $(WSJSON_OBJ)

OS ?= linux

ifeq ($(OS),windows)
	LDFLAGS += -lopengl32 -lgdi32 -lwinmn -lole32
endif

TARGET = game

all: run

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/$(TARGET): $(OBJ_FILES) $(TINY_OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TINY_OBJ): $(TINY_SRC)
	@echo "@Compiling tinyfiledialogs..."
	$(CC) -c $(TINY_SRC) -o $(TINY_OBJ) -I$(VENDOR)

$(WSJSON_OBJ): $(WSJSON_SRC)
	@echo "@Compiling wsJson..."
	$(CC) -c $(WSJSON_SRC) -o $(WSJSON_OBJ) -I$(VENDOR)/wsJson/include/wsJson

run: clean build/$(TARGET)
	./build/$(TARGET)

cloc: 
	cloc . --exclude-dir=vendor

clean:
	rm -rf $(OBJ_FILES) build

