
#include "playing/playing.h"
#include "playing/enemy.h"
#include "playing/path.h"

#include "GameManager.h"
#include "playing/tower.h"
#include <raylib.h>

void initPlaying(GameManager* gm) {
    Playing* playing = &gm->playing;
    initRandomPath(&playing->path);
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        playing->enemies[i] = (Enemy){0};
    }
    for (int32_t i = 0; i < MAX_TOWERS; i++) {
        playing->towers[i] = (Tower){0};
    }
}

void handlePlayingInput(GameManager* gm) {
    Playing* playing = &gm->playing;
    if (IsKeyPressed(KEY_L)) {
        for (int32_t i = 0; i < MAX_ENEMIES; i++) {
            if (!playing->enemies[i].active) {
                playing->enemies[i] = spawnEnemy();
                break;
            }
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int32_t i = 0; i < MAX_TOWERS; i++) {
            if (!playing->towers[i].active) {
                playing->towers[i] = placeTower(GetMousePosition());
                break;
            }
        }
    }
}

void updatePlaying(GameManager* gm) {
    Playing* playing = &gm->playing;
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        updateEnemy(gm, &playing->enemies[i]);
    }
}

void drawPlaying(GameManager* gm) {
    drawPath(&gm->playing.path);
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        if (gm->playing.enemies[i].active) drawEnemy(&gm->playing.enemies[i]);
    }

    for (int32_t i = 0; i < MAX_TOWERS; i++) {
        if (gm->playing.towers[i].active) drawTower(&gm->playing.towers[i]);
    }
}

