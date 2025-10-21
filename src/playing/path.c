
#include "playing/path.h"

void initRandomPath(Path *path) {
    path->start = (Vector2){50, 550};
    path->end = (Vector2){750, 50};

    float t = 0.0f;
    const float inc = 1.0f / PATH_POINTS_NUM;
    for (int32_t i = 0; i < PATH_POINTS_NUM; i++) {
        int32_t deltaX = GetRandomValue(0, PATH_MAX_DIFF) - PATH_MAX_DIFF / 2;
        int32_t deltaY = GetRandomValue(0, PATH_MAX_DIFF) - PATH_MAX_DIFF / 2;

        Vector2 p = Vector2Lerp(path->start, path->end, t);
        p.x += deltaX;
        p.y += deltaY;
        path->points[i] = p;
        printf("Point %d: %f %f\n", i, p.x, p.y);

        t += inc;
    }
}

void drawPath(Path *path) {
    // Start and End
    DrawLineEx(path->start, path->points[0], 5, WHITE);
    DrawLineEx(path->points[PATH_POINTS_NUM - 1], path->end, 5, WHITE);

    DrawCircle(path->start.x, path->start.y, 10, YELLOW);
    DrawCircle(path->end.x, path->end.y, 10, YELLOW);
    DrawCircle(path->points[0].x, path->points[0].y, 10, RED);
    for (int32_t i = 1; i < PATH_POINTS_NUM; i++) {
        DrawLineEx(path->points[i - 1], path->points[i], 5, WHITE);
        DrawCircle(path->points[i].x, path->points[i].y, 10, RED);
    }
}


