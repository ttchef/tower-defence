
#include "playing/tower.h"
#include <raylib.h>

Tower placeTower(Vector2 pos) {
    return (Tower) {
        .active = true,
        .pos = pos,
        .radius = 150.0f,
    };
}

void drawTower(Tower *tower) {
    Color outer = (Color){255, 255, 255, 80};
    Color inner = (Color){100, 100, 100, 65};
    DrawCircleGradient(tower->pos.x, tower->pos.y, tower->radius, inner, outer);
    DrawCircleLines(tower->pos.x, tower->pos.y, tower->radius, WHITE);
    DrawCircleGradient(tower->pos.x, tower->pos.y, 15, WHITE, BLACK);
}
