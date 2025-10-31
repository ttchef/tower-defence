
#ifndef MAP_H
#define MAP_H

#include "definies.h"

typedef struct MapState {
    Color backgroundColor;
} MapState;

void updateMapState(Manager* manager);
void drawMapState(Manager* manager);

#endif
