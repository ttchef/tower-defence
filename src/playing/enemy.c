
#include "playing/enemy.h"
#include "playing/path.h"
#include "playing/playing.h"
#include "GameManager.h"
#include <raymath.h>

Enemy spawnEnemy(EnemyType type) {
    Enemy e;
    e.pos = (Vector2){50.0f, 550.0f};
    e.interpolate = 0.0f;
    e.pointsIndex = -1;
    e.active = true;
    e.type = type;

    switch (type) {
        case GOBLIN:
            e.speed = 150.0f;
            e.size = 10;
            e.health = 100.0f;
            e.startHealth = 100.0f;
            e.value = 1;
            e.color = BLUE;
            break;
        case GOLEM:
            e.speed = 75.0f;
            e.size = 25;
            e.health = 300.0f;
            e.startHealth = 300.0f;
            e.value = 3;
            e.color = RED;
            break;
    };
    
    return e;
}

void updateEnemy(GameManager *gm, Enemy *enemy) {
    Playing* playing = &gm->playing;
    Vector2 newPos = {0};
    float diff = 1.0f;

    // End
    if (enemy->pointsIndex + 1 > PATH_POINTS_NUM) {
        enemy->pos = playing->path.end;
        enemy->active = false;
        playing->health -= enemy->value;
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
    DrawCircle(enemy->pos.x, enemy->pos.y, enemy->size, enemy->color); 

    if (enemy->health != enemy->startHealth) {

        float healthFactor = (float)enemy->health / (float)enemy->startHealth;

        DrawRectangle(enemy->pos.x - enemy->size * 2, enemy->pos.y - enemy->size * 2 - 5, enemy->size * 4, enemy->size, BLACK);
        DrawRectangle(enemy->pos.x - enemy->size * 2 + 2, enemy->pos.y - enemy->size * 2 - 3, (enemy->size * 4 * healthFactor) - 4, enemy->size - 4, RED);
    }
}

