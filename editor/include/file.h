
#ifndef FILE_H
#define FILE_H

#include "definies.h"

#define MAX_FILE_PATH 100

typedef struct FileState {
    bool mapOpen;
    bool newMap;
    char filepath[MAX_FILE_PATH];
} FileState;

void updateFileState(Manager* manager);
void drawFileState(Manager* manager);

#endif
