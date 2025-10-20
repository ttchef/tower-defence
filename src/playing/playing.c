
#include "playing/playing.h"
#include "playing/path.h"

#include "GameManager.h"

void initPlaying(Playing *playing) {
    initRandomPath(&playing->path);
}

void updatePlaying(GameManager* gm) {
    int x = gm->states.top;
    x++;
}

void drawPlaying(GameManager* gm) {
    drawPath(&gm->playing.path);
}

