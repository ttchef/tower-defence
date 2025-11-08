
#include "path.h"
#include <raylib.h>
#include <string.h>

void PathInitEmpty(Path *path) {
    path->points = NULL;
    path->pointsCount = 0;
    path->renderable = false;
}

void PathAddPoint(Path* path, Vector2 *point) {
    if (path->points == NULL || path->pointsCount == 0) {
        path->pointsCount++;
        path->points = malloc(sizeof(Vector2) * path->pointsCount);
        if (!path->points) {
            fprintf(stderr, "Failed to allocate points for path!\n");
            path->pointsCount = 0;
            return;
        }
    }
    else {
        path->pointsCount++;
        path->points = realloc(path->points, sizeof(Vector2) * path->pointsCount);
        if (!path->points) {
            fprintf(stderr, "Failed to reallocate points for path!\n");
            exit(-1);
        }
    }
    memcpy(&path->points[path->pointsCount - 1], point, sizeof(Vector2));
    if (!path->renderable) path->renderable = true;
}

void PathDraw(Path *path) {
    if (!path->renderable) return;

    // Lines
    if (path->pointsCount > 1) {
        for (int32_t i = 0; i < path->pointsCount - 1; i++) {
            DrawLine(path->points[i].x, path->points[i].y, path->points[i + 1].x, path->points[i + 1].y, WHITE);
        }
    }

    // Circles
    for (int32_t i = 0; i < path->pointsCount; i++) {
        DrawCircle(path->points[i].x, path->points[i].y, 10, RED); 
    }
}

