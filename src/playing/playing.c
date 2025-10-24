
#include "playing/playing.h"
#include "playing/enemy.h"
#include "playing/path.h"

#include "GameManager.h"
#include "playing/projectile.h"
#include "playing/tower.h"
#include <raylib.h>

const char* towerNames[TOWER_TYPE_NUM] = {
    "Rock",
    "Plant",
    "Mountain",
};

Tower towerProto[TOWER_TYPE_NUM];


void initPlaying(GameManager* gm) {
    Playing* playing = &gm->playing;
    playing->guiWidth = 300;
    playing->guiOffset = gm->screenWidth - playing->guiWidth;

    // Path
    playing->path.start = (Vector2){ 50, gm->screenHeight - 50};
    playing->path.end = (Vector2){playing->guiOffset - 50, 50};
    initRandomPath(gm);

    playing->money = 100;
    playing->health = 100;

    playing->towerTex[ROCK].tex = LoadTexture("res/rock.jpg");
    playing->towerTex[PLANT].tex = LoadTexture("res/plant.jpg");
    playing->towerTex[MOUNTAIN].tex = LoadTexture("res/mountain.jpg");

    // Towers 
    Playing* p = playing;
    int32_t boxWidth = 100;
    int32_t boxHeight = 150;
    int32_t offset1 = p->guiOffset + 20;
    int32_t offset2 = p->guiOffset + boxWidth + 50;

    int32_t offsetY = 20;
    for (int32_t i = 0; i < TOWER_TYPE_NUM; i++) {
        int32_t offset = (i % 2 == 0) ? offset1 : offset2;
        if (i != 0 && i % 2 == 0) offsetY += boxHeight + 20;
            playing->towerTex[i].pos.x = offset;
            playing->towerTex[i].pos.y = offsetY;
            playing->towerTex[i].width = boxWidth;
            playing->towerTex[i].height = boxHeight;
    }

    playing->currentTower = ROCK;

    // Init towerProto
    for (int32_t i = 0; i < TOWER_TYPE_NUM; i++) {
        towerProto[i] = placeTower(i, (Vector2){0, 0});
    }
}

void handlePlayingInput(GameManager* gm) {
    Playing* playing = &gm->playing;
    if (IsKeyPressed(KEY_L)) {
        for (int32_t i = 0; i < MAX_ENEMIES; i++) {
            if (!playing->enemies[i].active) {
                playing->enemies[i] = spawnEnemy(GOBLIN);
                break;
            }
        }
    }
    if (IsKeyPressed(KEY_K)) {
        for (int32_t i = 0; i < MAX_ENEMIES; i++) {
            if (!playing->enemies[i].active) {
                playing->enemies[i] = spawnEnemy(GOLEM);
                break;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();
    
        for (int32_t i = 0; i < TOWER_TYPE_NUM; i++) {
            TowerTexturePos t = playing->towerTex[i];
             
            if (pos.x >= t.pos.x &&
                pos.x < t.pos.x + t.width &&
                pos.y >= t.pos.y &&
                pos.y < t.pos.y + t.height) {
                playing->currentTower = i;
            }
        }

        if (pos.x > playing->guiOffset) return;
        for (int32_t i = 0; i < MAX_TOWERS; i++) {
            if (!playing->towers[i].active) {
                playing->towers[i] = placeTower(playing->currentTower, GetMousePosition());
                if (!(playing->money >= playing->towers[i].price)) {
                    playing->towers[i].active = false;
                    break;
                }
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
    for (int32_t i = 0; i < TOWER_TYPE_NUM; i++) {
        TowerTexturePos t = p->towerTex[i];
        DrawRectangle(t.pos.x, t.pos.y, t.width, t.height, DARKGRAY);
        DrawTexturePro(t.tex, 
                        (Rectangle){t.pos.x + 5, t.pos.y + 5, t.tex.width, t.tex.height},
                        (Rectangle){t.pos.x + 5, t.pos.y + 5, t.width - 10, t.width - 10},
                        (Vector2){0, 0}, 0, WHITE);
        const char* text = TextFormat("%s: %d$", towerNames[i], towerProto[i].price);
        int32_t fontSize = 18;
        while (MeasureText(text, fontSize) >= t.width - 20) {
            fontSize--;
        }
        
        if (fontSize < 15) {
            const char* name = TextFormat("%s", towerNames[i]);
            const char* price = TextFormat("%d$", towerProto[i].price);
            DrawText(name, t.pos.x + 10, t.pos.y + t.height / 1.4, 18, WHITE);
            DrawText(price, t.pos.x + + t.width / 2 - 10, t.pos.y + t.height / 1.2, 18, WHITE);
        }
        else {
            DrawText(text, t.pos.x + 10, t.pos.y + t.height / 1.3, fontSize, WHITE);
        }
    }
    
    DrawText(TextFormat("Money: %d", p->money), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Health: %d", p->health), 10, 40,  20, RAYWHITE);
}

