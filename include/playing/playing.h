
#ifndef PLAYING_H
#define PLAYING_H

#include "definies.h"
#include "path.h"

typedef struct {
    Path path;
} Playing;

void initPlaying(Playing* playing);
void updatePlaying(GameManager* gm);
void drawPlaying(GameManager* gm);

#endif
