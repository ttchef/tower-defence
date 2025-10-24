

#ifndef TOWER_H
#define TOWER_H

#include "definies.h"
#include "enemy.h"
#include "playing/projectile.h"

#define MAX_TOWERS 100

typedef enum {
    ROCK,
    PLANT,
    MOUNTAIN,

    TOWER_TYPE_NUM,
} TowerType;


typedef struct Tower {
    TowerType type;
    bool active;
    Vector2 pos;
    float radius;
    float cooldown;
    float sleep;
    float damage;
    int32_t price;
    bool areaOfEffect;
    int32_t explosionRadius;
    int32_t size;
} Tower;

Tower placeTower(TowerType tower, Vector2 pos);
void updateTower(Tower* tower, Enemy* enemis, Projectile* proj);
void drawTower(Tower* tower);


#endif
