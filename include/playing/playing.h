
#ifndef PLAYING_H
#define PLAYING_H

#include "definies.h"
#include "path.h"
#include "enemy.h"
#include "playing/projectile.h"
#include "playing/tower.h"

typedef struct {
    Path path;
    Enemy enemies[MAX_ENEMIES];
    Tower towers[MAX_TOWERS];
    Projectile proj[MAX_PROJECTILES];
} Playing;

void initPlaying(GameManager* gm);
void handlePlayingInput(GameManager* gm);
void updatePlaying(GameManager* gm, float dt);
void drawPlaying(GameManager* gm);

#endif
