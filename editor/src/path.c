
#include "path.h"
#include <raylib.h>
#include <string.h>

void PathInitEmpty(Path *path) {
    path->points = NULL;
    path->pointsCount = 0;
    path->controlPoints = NULL;
    path->controlPointsCount = 0;
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
        path->controlPointsCount++;
        path->controlPoints = malloc(sizeof(Vector2) * path->controlPointsCount);
        if (!path->controlPoints) {
            fprintf(stderr, "Failed to allocate conrtol points for path!\n");
            path->controlPointsCount = 0;
            return;
        }

        memcpy(&path->controlPoints[path->controlPointsCount - 1], point, sizeof(Vector2));

        // temp offset
        path->controlPoints[path->controlPointsCount - 1].x -= 30;
        path->controlPoints[path->controlPointsCount - 1].y += 30;
    }
    else {
        path->pointsCount++;
        path->points = realloc(path->points, sizeof(Vector2) * path->pointsCount);
        if (!path->points) {
            fprintf(stderr, "Failed to reallocate points for path!\n");
            exit(-1);
        }

        if (path->pointsCount <= 2) {
            path->controlPointsCount++;
            path->controlPoints = realloc(path->controlPoints, sizeof(Vector2) * path->controlPointsCount);
            if (!path->controlPoints) {
                fprintf(stderr, "Failed to reallocate points for path!\n");
                exit(-1);
            }
            memcpy(&path->controlPoints[path->controlPointsCount - 1], point, sizeof(Vector2));
            path->controlPoints[path->controlPointsCount - 1].x -= 30;
            path->controlPoints[path->controlPointsCount - 1].y += 30;
        }
        else { 
            path->controlPointsCount += 2;
            path->controlPoints = realloc(path->controlPoints, sizeof(Vector2) * path->controlPointsCount);
            if (!path->controlPoints) {
                fprintf(stderr, "Failed to reallocate points for path!\n");
                exit(-1);
            }
            memcpy(&path->controlPoints[path->controlPointsCount - 1], point, sizeof(Vector2));
            path->controlPoints[path->controlPointsCount - 1].x -= 30;
            path->controlPoints[path->controlPointsCount - 1].y += 30;

            memcpy(&path->controlPoints[path->controlPointsCount - 2], &path->points[path->pointsCount - 2], sizeof(Vector2));
            path->controlPoints[path->controlPointsCount - 2].x += 30;
            path->controlPoints[path->controlPointsCount - 2].y -= 30;
        }
    }
    memcpy(&path->points[path->pointsCount - 1], point, sizeof(Vector2));


    if (!path->renderable) path->renderable = true;
}

void PathDraw(Path *path) {
    if (!path->renderable) return;

    // Control Points
    // Lines
    DrawLine(path->points[0].x, path->points[0].y, path->controlPoints[0].x, path->controlPoints[0].y, SKYBLUE);
    
    for (int32_t i = 1; i < path->pointsCount - 1; i++) {
        DrawLine(path->points[i].x, path->points[i].y, path->controlPoints[i * 2].x, path->controlPoints[i * 2].y, SKYBLUE);
        DrawLine(path->points[i].x, path->points[i].y, path->controlPoints[i * 2 - 1].x, path->controlPoints[i * 2 - 1].y, SKYBLUE);
    }

    // Draw End Line
    if (path->pointsCount > 1) {
        DrawLine(path->points[path->pointsCount - 1].x, path->points[path->pointsCount - 1].y, 
                 path->controlPoints[path->controlPointsCount - 1].x,
                 path->controlPoints[path->controlPointsCount - 1].y, SKYBLUE);
    }

    // Circles
    for (int32_t i = 0; i < path->controlPointsCount; i++) {
        DrawCircle(path->controlPoints[i].x, path->controlPoints[i].y, 5, YELLOW);
    }
        
    // Points
    // Lines
    if (path->pointsCount > 1) DrawSplineSegmentBezierCubic(path->points[0], path->controlPoints[0], path->controlPoints[1], path->points[1], 4, WHITE);
    if (path->pointsCount > 1) {
        for (int32_t i = 1; i < path->pointsCount - 1; i++) {
            //DrawLine(path->points[i].x, path->points[i].y, path->points[i + 1].x, path->points[i + 1].y, WHITE);
            DrawSplineSegmentBezierCubic(path->points[i], path->controlPoints[i * 2 - 1], path->controlPoints[i * 2], path->points[i + 1], 4, WHITE);
        }
    }

    // Circles
    for (int32_t i = 0; i < path->pointsCount; i++) {
        DrawCircle(path->points[i].x, path->points[i].y, 10, RED); 
    }
}

