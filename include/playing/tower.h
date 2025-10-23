

#ifndef TOWER_H
#define TOWER_H

#include "definies.h"
#include "enemy.h"
#include "playing/projectile.h"

#define MAX_TOWERS 100

typedef struct Tower {
    bool active;
    Vector2 pos;
    float radius;
    float cooldown;
    float sleep;
} Tower;

Tower placeTower(Vector2 pos);
void updateTower(Tower* tower, Enemy* enemis, Projectile* proj);
void drawTower(Tower* tower);


#endif
