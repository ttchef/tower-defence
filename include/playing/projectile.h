
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
} Projectile;

Projectile spawnProjectile(Vector2 pos, int32_t index);
void updateProjectile(Projectile* proj, Enemy* enemies, float dt);
void drawProjectile(Projectile* proj);

#endif
