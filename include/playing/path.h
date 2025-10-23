
#ifndef PATH_H
#define PATH_H

#include "definies.h"

#define PATH_POINTS_NUM 10
#define PATH_MAX_DIFF 150

typedef struct {
    Vector2 points[PATH_POINTS_NUM];
    Vector2 start;
    Vector2 end;
} Path;

void initRandomPath(GameManager* gm);
void drawPath(GameManager* gm);

#endif
