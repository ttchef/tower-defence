
#ifndef PATH_H
#define PATH_H

#include "definies.h"

typedef struct Path {
    Vector2* points;
    int32_t pointsCount;
    bool renderable;
} Path;

void PathInitEmpty(Path* path);
void PathAddPoint(Path* path, Vector2* point);
void PathDraw(Path* path);

#endif
