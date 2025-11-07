
#ifndef MAP_H
#define MAP_H

#include "definies.h"
#include "wsJson/ws_json.h"
#include "file.h"

#define MAX_MAP_NAME_COUNT 28

typedef struct Map {
    char name[MAX_MAP_NAME_COUNT];
    Color backgroundColor;

    Vector2* pathPoints;
    int32_t pathPointsCount;
} Map;

typedef enum MapStateTabType {
    MAP_STATE_TAB_OVERALL,
    MAP_STATE_TAB_PATH,
    MAP_STATE_TAB_TEXTURES,

    MAP_STATE_TAB_NUM,
} MapStateTabType;

typedef struct MapState {
    wsJson* json;
    Map map;
    const char* filepath;
    bool saved;
    MapStateTabType tabs[MAP_STATE_TAB_NUM];
    int32_t currentTab;
} MapState;

void initMapState(Manager* manager);
void updateMapState(Manager* manager);
void drawMapState(Manager* manager);
void drawMapStateGui(Manager* manager);

void deinitMapState(Manager* manager);

void newMap(Manager* manager, const char* filepath);
void openMap(Manager* manager, const char* filepath);
void saveMapAs(Manager* manager, const char* filepath);
void saveMap(Manager* manager);

#endif
