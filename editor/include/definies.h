
#ifndef DEFINIES_H
#define DEFINIES_H

#ifdef _WIN32
    #define RAYLIB_NOMAIN
#endif

#include <raylib.h>
#include <raygui.h>

#include <stdint.h> 
#include <stdbool.h> 
#include <stdlib.h> 
#include <stdio.h>

#define ARRAY_COUNT(a) (sizeof((a)) / sizeof((a)[0]))

typedef struct Manager Manager;

#endif
