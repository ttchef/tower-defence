
#ifndef ENEMY_H
#define ENEMY_H

#include "definies.h"

#define MAX_ENEMIES 100

typedef struct {
    bool active;
    Vector2 pos;
} Enemy;

Enemy spawnEnemy();
void drawEnemy(Enemy* enemy);

#endif
