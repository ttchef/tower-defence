
CC = gcc

CFLAGS_DEBUG = -Wall -Wextra -Werror -Wpedantic -g -O0 -fsanitize=address -fsanitize=undefined -std=c99
CFLAGS_RELEASE = -O2

LDFLAGS = -lraylib -lm

VENDOR = vendor

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
	CC = x86_64-w64-mingw32-gcc
	TARGET = game.exe
	LDFLAGS += -lopengl32 -lgdi32 -lwinmm -lole32 -lcomdlg32 -static
	CFLAGS += -D_WIN32
else
	CC = gcc
	TARGET = game
	LDFLAGS = -lraylib -lm
endif

BUILD ?= debug 

ifeq ($(BUILD), release)
	CFLAGS = -Iinclude -I$(VENDOR) $(CFLAGS_RELEASE)
else 
	CFLAGS = -Iinclude -I$(VENDOR) $(CFLAGS_DEBUG)
endif

all: run

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/$(TARGET): $(OBJ_FILES)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TINY_OBJ): $(TINY_SRC)
	@echo "@Compiling tinyfiledialogs..."
	$(CC) -c $(TINY_SRC) -o $(TINY_OBJ)

$(WSJSON_OBJ): $(WSJSON_SRC)
	@echo "@Compiling wsJson..."
	$(CC) -c $(WSJSON_SRC) -o $(WSJSON_OBJ) -I$(VENDOR)/wsJson/include/wsJson

run: clean build/$(TARGET)
	./build/$(TARGET)

cloc: 
	cloc . --exclude-dir=vendor

clean:
	rm -rf $(OBJ_FILES) build

