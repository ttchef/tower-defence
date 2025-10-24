
#ifndef PLAYING_H
#define PLAYING_H

#include "definies.h"
#include "path.h"
#include "enemy.h"
#include "playing/projectile.h"
#include "playing/tower.h"

typedef struct {
    Texture2D tex;
    Vector2 pos;
    int32_t width;
    int32_t height;
} TowerTexturePos;

typedef enum {
    GUI_STATE_TOWER_DISPLAY,
    GUI_STATE_TOWER_STATS,
} PlayingGuiState;

typedef struct {
    Path path;
    Enemy enemies[MAX_ENEMIES];
    Tower towers[MAX_TOWERS];
    Projectile proj[MAX_PROJECTILES];

    int32_t money;
    int32_t health;
    int32_t guiOffset;
    int32_t guiWidth;

    int32_t selectedTower;
    int32_t currentTower;
    PlayingGuiState guiState;
    TowerTexturePos towerTex[TOWER_TYPE_NUM];
} Playing;

void initPlaying(GameManager* gm);
void handlePlayingInput(GameManager* gm);
void updatePlaying(GameManager* gm, float dt);
void drawPlaying(GameManager* gm);
void drawGui(GameManager* gm);
void drawGuiTowerDisplay(GameManager* gm);
void drawGuiTowerStats(GameManager* gm);

#endif

