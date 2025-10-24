
#include "GameManager.h"
#include "playing/playing.h" 
#include "playing/enemy.h"
#include "playing/projectile.h"
#include <raymath.h>

Projectile spawnProjectile(Vector2 pos, int32_t index, int32_t damage, int32_t explosionRadius) {
    return (Projectile){
        .pos = pos,
        .index = index,
        .speed = 20.0f,
        .active = true,
        .interpolate = 0.0f,
        .size = 5,
        .damage = damage,
        .explosionRadius = explosionRadius,
        .areaOFEffect = (explosionRadius != 0) ? true : false,
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
        if (proj->areaOFEffect) {
            for (int32_t i = 0; i < MAX_ENEMIES; i++) {
                if (!enemies[i].active) continue;;
                float dist = Vector2Distance(proj->pos, enemies[i].pos);
                if (dist < proj->size + enemies[i].size + proj->explosionRadius) {
                    enemies[i].health -= proj->damage;
                    if (enemies[i].health <= 0) {
                        gm->playing.money += enemies[i].value;
                        enemies[i].active = false;
                    }
                }
            }
        }
        else {
            enemies[proj->index].health -= proj->damage;
            if (enemies[proj->index].health <= 0) {
                gm->playing.money += enemies[proj->index].value;
                enemies[proj->index].active = false;
        
            }   
        }
        return;
    }

    proj->pos = Vector2Lerp(proj->pos, target, proj->interpolate);
    proj->interpolate += (proj->speed * dt) / diff;
}

void drawProjectile(Projectile *proj) {
    DrawCircle(proj->pos.x, proj->pos.y, proj->size, WHITE);
} 
