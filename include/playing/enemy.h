
#ifndef ENEMY_H
#define ENEMY_H

#include "definies.h"

#define MAX_ENEMIES 100

typedef struct {
    bool active;
    float interpolate;
    int32_t pointsIndex;
    float speed;
    int32_t size;
    Vector2 pos;
} Enemy;

Enemy spawnEnemy();
void updateEnemy(GameManager* gm, Enemy* enemy);
void drawEnemy(Enemy* enemy);

#endif
