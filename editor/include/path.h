
#ifndef PATH_H
#define PATH_H

#include "definies.h"

typedef enum PathPointType {
    PATH_POINT_TYPE_POINT,
    PATH_POINT_TYPE_CONRTOL_POINT,
} PathPointType;

typedef struct Path {
    Vector2* points;
    int32_t pointsCount;
    Vector2* controlPoints;
    int32_t controlPointsCount;
    bool renderable;
} Path;

void PathInitEmpty(Path* path);
void PathAddPoint(Path* path, Vector2* point);
void PathDraw(Path* path);

#endif
