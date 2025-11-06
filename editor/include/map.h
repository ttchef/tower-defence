
#ifndef MAP_H
#define MAP_H

#include "definies.h"
#include "wsJson/ws_json.h"
#include "file.h"

typedef struct Map {
    Color backgroundColor;

    Vector2* pathPoints;
    int32_t pathPointsCount;
} Map;

typedef struct MapState {
    wsJson* json;
    Map map;
    path_t filepath;
} MapState;

void updateMapState(Manager* manager);
void drawMapState(Manager* manager);
void drawMapStateGui(Manager* manager);

void deinitMapState(Manager* manager);

void newMap(Manager* manager, path_t filepath);
void openMap(Manager* manager, path_t filepath);
void saveMapAs(Manager* manager, path_t filepath);
void saveMap(Manager* manager);

#endif
