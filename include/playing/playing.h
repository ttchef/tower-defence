
#ifndef PLAYING_H
#define PLAYING_H

#include "definies.h"
#include "path.h"
#include "enemy.h"
#include "playing/tower.h"

typedef struct {
    Path path;
    Enemy enemies[MAX_ENEMIES];
    Tower towers[MAX_TOWERS];
} Playing;

void initPlaying(GameManager* gm);
void handlePlayingInput(GameManager* gm);
void updatePlaying(GameManager* gm);
void drawPlaying(GameManager* gm);

#endif
