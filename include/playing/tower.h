

#ifndef TOWER_H
#define TOWER_H

#include "definies.h"
#include "enemy.h"

#define MAX_TOWERS 100

typedef struct Tower {
    bool active;
    Vector2 pos;
    float radius;
} Tower;

Tower placeTower(Vector2 pos);
void updateTower(Tower* tower, Enemy* enemis);
void drawTower(Tower* tower);


#endif
