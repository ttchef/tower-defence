
#ifndef PLAYING_H
#define PLAYING_H

#include "definies.h"
#include "path.h"
#include "enemy.h"

typedef struct {
    Path path;
    Enemy enemies[MAX_ENEMIES];
} Playing;

void initPlaying(GameManager* gm);
void handlePlayingInput(GameManager* gm);
void updatePlaying(GameManager* gm);
void drawPlaying(GameManager* gm);

#endif
