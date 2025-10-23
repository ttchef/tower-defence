
#include "playing/enemy.h"
#include "playing/path.h"
#include "playing/playing.h"
#include "GameManager.h"
#include <raymath.h>

Enemy spawnEnemy() {
    return (Enemy) {
        .pos = (Vector2){50.0f, 550.0f},
        .active = true,
        .interpolate = 0.0f,
        .pointsIndex = -1,
        .speed = 150.0f,
        .size = 10,
    };
}

void updateEnemy(GameManager *gm, Enemy *enemy) {
    Playing* playing = &gm->playing;
    Vector2 newPos = {0};
    float diff = 1.0f;

    // End
    if (enemy->pointsIndex + 1 > PATH_POINTS_NUM) {
        enemy->pos = playing->path.end;
        enemy->active = false;
        playing->health--;
        return;
    }

    else if (enemy->pointsIndex + 1 == PATH_POINTS_NUM) {

        diff = Vector2Distance(playing->path.points[PATH_POINTS_NUM - 1], playing->path.end);
        newPos = Vector2Lerp(playing->path.points[PATH_POINTS_NUM - 1], playing->path.end, enemy->interpolate);
    }
    else if (enemy->pointsIndex == -1) {
        diff = Vector2Distance(playing->path.start, playing->path.points[0]);
        newPos = Vector2Lerp(playing->path.start, playing->path.points[0], enemy->interpolate);
    }
    else {
        diff = Vector2Distance(playing->path.points[enemy->pointsIndex], playing->path.points[enemy->pointsIndex + 1]);
        newPos = Vector2Lerp(playing->path.points[enemy->pointsIndex], playing->path.points[enemy->pointsIndex + 1], enemy->interpolate);
    }
    enemy->pos = newPos;
    enemy->interpolate += (enemy->speed * gm->deltaTime) / diff;
    
    if (enemy->interpolate >= 1.0f) {
        enemy->interpolate = 0.0f;
        enemy->pointsIndex++;
    }
}

void drawEnemy(Enemy *enemy) {
        DrawCircle(enemy->pos.x, enemy->pos.y, enemy->size, BLUE);    
}

