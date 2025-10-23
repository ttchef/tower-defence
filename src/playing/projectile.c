
#include "playing/enemy.h"
#include "playing/projectile.h"
#include <raymath.h>

Projectile spawnProjectile(Vector2 pos, int32_t index) {
    return (Projectile){
        .pos = pos,
        .index = index,
        .speed = 20.0f,
        .active = true,
        .interpolate = 0.0f,
    };  
}

void updateProjectile(Projectile *proj, Enemy* enemies, float dt) {
    if (proj->interpolate >= 1.0f) {
        proj->active = false;
        enemies[proj->index].active = false;
        return;
    }
    Vector2 target = enemies[proj->index].pos;
    float diff = Vector2Distance(proj->pos, target);

    proj->pos = Vector2Lerp(proj->pos, target, proj->interpolate);
    proj->interpolate += (proj->speed * dt) / diff;
}

void drawProjectile(Projectile *proj) {
    DrawCircle(proj->pos.x, proj->pos.y, 5, WHITE);
}
