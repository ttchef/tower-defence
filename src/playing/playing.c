
#include "playing/playing.h"
#include "playing/enemy.h"
#include "playing/path.h"

#include "GameManager.h"

void initPlaying(GameManager* gm) {
    Playing* playing = &gm->playing;
    initRandomPath(&playing->path);
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        playing->enemies[i] = (Enemy){0};
    }
}

void handlePlayingInput(GameManager* gm) {
    Playing* playing = &gm->playing;
    if (IsKeyDown(KEY_L)) {
        for (int32_t i = 0; i < MAX_ENEMIES; i++) {
            if (!playing->enemies[i].active) {
                playing->enemies[i] = spawnEnemy();
            }
        }
    }
}

void updatePlaying(GameManager* gm) {
    int x = gm->states.top;
    x++;
}

void drawPlaying(GameManager* gm) {
    drawPath(&gm->playing.path);
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        drawEnemy(&gm->playing.enemies[i]);
    }
}

