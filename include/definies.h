
#ifndef DEFINIES_h
#define DEFINIES_h

#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #define RAYLIB_NOMAIN

    #include <windows.h>

    int main();
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        (void)hInstance;
        (void)hPrevInstance;
        (void)lpCmdLine;
        (void)nCmdShow;
        return main();
    }
#endif

#include <raylib.h>
#include <raymath.h>

#define GAME_ERROR -1
#define GAME_SUCCSESS 0

// idk if they really help
#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtint_expect(!!(x), 0)

#define STATIC_ASSERT(expr) _Static_assert(expr, #expr)
#define WUNUSED __attribute__((warn_unused_result))

typedef struct GameManager GameManager;

#endif
