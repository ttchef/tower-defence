
#include "GameManager.h"
#include "playing/playing.h" 
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
        .size = 5,
    };  
}

void updateProjectile(Projectile *proj, Enemy* enemies, float dt, GameManager* gm) {
    if (!enemies[proj->index].active) {
        proj->active = false;
        return;
    }
    Vector2 target = enemies[proj->index].pos;
    float diff = Vector2Distance(proj->pos, target);

    /*
    if (proj->interpolate >= 1.0f) {
        proj->active = false;
        enemies[proj->index].active = false;
        return;
    }
    */

    if (diff < proj->size + enemies[proj->index].size) {
        proj->active = false;
        enemies[proj->index].active = false;
        gm->playing.money++;
        return;
    }

    proj->pos = Vector2Lerp(proj->pos, target, proj->interpolate);
    proj->interpolate += (proj->speed * dt) / diff;
}

void drawProjectile(Projectile *proj) {
    DrawCircle(proj->pos.x, proj->pos.y, proj->size, WHITE);
} 
