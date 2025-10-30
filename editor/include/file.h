
#ifndef FILE_H
#define FILE_H

#include "definies.h"

typedef struct FileState {
    const char* l;
} FileState;

void updateFileState(Manager* manager);
void drawFileState(Manager* manager);

#endif
