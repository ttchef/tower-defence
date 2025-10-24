
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "definies.h"

#define MAX_PROJECTILES 1000

typedef struct Projectile  {
    Vector2 pos;
    int32_t index;
    float speed;
    bool active;
    float interpolate;
    int32_t size;
    int32_t damage;
    bool areaOFEffect;
    int32_t explosionRadius;
} Projectile;

Projectile spawnProjectile(Vector2 pos, int32_t index, int32_t damage, int32_t explosionRadius);
void updateProjectile(Projectile* proj, Enemy* enemies, float dt, GameManager* gm);
void drawProjectile(Projectile* proj);

#endif
