
#include "playing/playing.h"
#include "playing/enemy.h"
#include "playing/path.h"

#include "GameManager.h"
#include "playing/projectile.h"
#include "playing/tower.h"
#include <raylib.h>

void initPlaying(GameManager* gm) {
    Playing* playing = &gm->playing;
    playing->guiWidth = 300;
    playing->guiOffset = gm->screenWidth - playing->guiWidth;

    // Path
    playing->path.start = (Vector2){ 50, gm->screenHeight - 50};
    playing->path.end = (Vector2){playing->guiOffset - 50, 50};
    initRandomPath(gm);

    playing->money = 1000;
    playing->health = 100;

    playing->towerTex[ROCK] = LoadTexture("res/rock.jpg");
    playing->towerTex[PLANT] = LoadTexture("res/plant.jpg");
    playing->towerTex[MOUNTAIN] = LoadTexture("res/mountain.jpg");
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
        Vector2 pos = GetMousePosition();
        if (pos.x > playing->guiOffset) return;
        if (playing->money < 350) return;
        for (int32_t i = 0; i < MAX_TOWERS; i++) {
            if (!playing->towers[i].active) {
                playing->towers[i] = placeTower(ROCK, GetMousePosition());
                playing->money -= playing->towers[i].price;
                break;
            }
        }
    }
}

void updatePlaying(GameManager* gm, float dt) {
    Playing* playing = &gm->playing;
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        if (gm->playing.enemies[i].active) updateEnemy(gm, &playing->enemies[i]);
    }
    for (int32_t i = 0; i < MAX_TOWERS; i++) {
        if (gm->playing.towers[i].active) updateTower(&gm->playing.towers[i], gm->playing.enemies, playing->proj);
    }
    for (int32_t i = 0; i < MAX_PROJECTILES; i++) {
        if (gm->playing.proj[i].active) updateProjectile(&playing->proj[i], playing->enemies, dt, gm);
    }
}

void drawPlaying(GameManager* gm) {
    drawPath(gm);
    for (int32_t i = 0; i < MAX_ENEMIES; i++) {
        if (gm->playing.enemies[i].active) drawEnemy(&gm->playing.enemies[i]);
    }

    for (int32_t i = 0; i < MAX_TOWERS; i++) {
        if (gm->playing.towers[i].active) drawTower(&gm->playing.towers[i]);
    }
    for (int32_t i = 0; i < MAX_PROJECTILES; i++) {
        if (gm->playing.proj[i].active) drawProjectile(&gm->playing.proj[i]);
    }

    drawGui(gm);
}

void drawGui(GameManager *gm) {
    Playing* p = &gm->playing;

    DrawRectangle(p->guiOffset, 0, p->guiWidth, gm->screenHeight, GRAY);
    
    // Towers 
    int32_t boxWidth = 100;
    int32_t offset1 = p->guiOffset + 20;
    int32_t offset2 = p->guiOffset + boxWidth + 50;

    int32_t offsetY = 20;
    for (int32_t i = 0; i < TOWER_TYPE_NUM; i++) {
        int32_t offset = (i % 2 == 0) ? offset1 : offset2;
        if (i != 0 && i % 2 == 0) offsetY += boxWidth + 20;

        DrawRectangle(offset, offsetY, boxWidth, boxWidth, DARKGRAY);
        DrawTexturePro(p->towerTex[i], 
                        (Rectangle){offset + 5, offsetY + 5, p->towerTex->width, p->towerTex->height},
                        (Rectangle){offset + 5, offsetY + 5, boxWidth - 10, boxWidth - 10},
                        (Vector2){0, 0}, 0, WHITE);
    }
    
    DrawText(TextFormat("Money: %d", p->money), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Health: %d", p->health), 10, 40,  20, RAYWHITE);
}

