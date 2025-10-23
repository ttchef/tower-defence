
#include "playing/tower.h"
#include "playing/enemy.h"
#include "playing/projectile.h"
#include <raylib.h>

Tower placeTower(Vector2 pos) {
    return (Tower) {
        .active = true,
        .pos = pos,
        .radius = 150.0f,
        .cooldown = 1.0f,
        .sleep = 0.0f,
    };
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
                    proj[j] = spawnProjectile(tower->pos, i);
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
