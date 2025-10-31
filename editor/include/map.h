
#ifndef MAP_H
#define MAP_H

#include "definies.h"

typedef struct MapState {
    int32_t temp;
} MapState;

void updateMapState(Manager* manager);
void drawMapState(Manager* manager);

#endif
