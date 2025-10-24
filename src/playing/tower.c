
#include "playing/tower.h"
#include "playing/enemy.h"
#include "playing/projectile.h"
#include <raylib.h>

Tower placeTower(TowerType type, Vector2 pos) {
    Tower t = {
        .active = true,
        .pos = pos,
    };

    switch (type) {
        case ROCK:
            t.radius = 100.0f;
            t.cooldown = 1.0f;
            t.damage = 100.0f;
            t.price = 40;
            t.areaOfEffect = false;
            break;
        case PLANT:
            t.radius = 175.0f;
            t.cooldown = 0.5f;
            t.damage = 70.0f;
            t.price = 70;
            t.areaOfEffect = false;
            break;
        case MOUNTAIN:
            t.radius = 250.0f;
            t.cooldown = 4.0f;
            t.damage = 300.0f;
            t.price = 170;
            t.areaOfEffect = true;
            t.explosionRadius = 100.0f;
        case TOWER_TYPE_NUM:
            break;
    };
    return t;
}

void updateTower(Tower *tower, Enemy* enemies, Projectile* proj) {
    tower->sleep += GetFrameTime();
    if (tower->sleep < tower->cooldown) return;

    for (int32_t i = 0;i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) continue;

        // is in range?
        float diff = Vector2Distance(tower->pos, enemies[i].pos);
        if (diff <= tower->radius + enemies[i].size) {
            for (int32_t j = 0; j < MAX_PROJECTILES; j++) {
                if (!proj[j].active) {
                    proj[j] = spawnProjectile(tower->pos, i, tower->damage, tower->explosionRadius);
                    break;
                }
            }
            tower->sleep = 0.0f;
            break;
        }
    }
}

void drawTower(Tower *tower) {
    Color outer = (Color){255, 255, 255, 80};
    Color inner = (Color){100, 100, 100, 65};
    DrawCircleGradient(tower->pos.x, tower->pos.y, tower->radius, inner, outer);
    DrawCircleLines(tower->pos.x, tower->pos.y, tower->radius, WHITE);
    DrawCircleGradient(tower->pos.x, tower->pos.y, 15, WHITE, BLACK);
}
