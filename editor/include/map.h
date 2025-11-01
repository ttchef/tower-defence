
#ifndef MAP_H
#define MAP_H

#include "definies.h"
#include "wsJson/ws_json.h"

typedef struct Map {
    Color backgroundColor;

    Vector2* pathPoints;
    int32_t pathPointsCount;
} Map;

typedef struct MapState {
    wsJson json;
    Map map;
    bool change;
} MapState;

void updateMapState(Manager* manager);
void drawMapState(Manager* manager);

void deinitMapState(Manager* manager);

#endif
