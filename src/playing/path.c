
#include "playing/path.h"
#include <raylib.h>
#include <raymath.h>

void initRandomPath(Path *path) {
    path->start = (Vector2){0, 600};
    path->end = (Vector2){800, 0};

    float t = 0.0f;
    float inc = 1.0f / PATH_POINTS_NUM;
    for (int32_t i = 0; i < PATH_POINTS_NUM; i++) {
        int32_t deltaX = GetRandomValue(0, PATH_MAX_DIFF) - PATH_MAX_DIFF / 2;
        int32_t deltaY = GetRandomValue(0, PATH_MAX_DIFF) - PATH_MAX_DIFF / 2;

        Vector2 p = Vector2Lerp(path->start, path->end, t);
        p.x += deltaX;
        p.y += deltaY;
        path->points[i] = p;

        t += inc;
    }
}

void drawPath(Path *path) {
    // Start and End
    DrawLineEx(path->start, path->points[0], 10, WHITE);
    DrawLineEx(path->points[PATH_POINTS_NUM - 1], path->end, 10, WHITE);
    for (int32_t i = 1; i < PATH_POINTS_NUM; i++) {
        DrawLineEx(path->points[i - 1], path->points[i], 10, WHITE);
    }
}


