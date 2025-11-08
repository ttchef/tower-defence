
#ifndef MAP_H
#define MAP_H

#include "definies.h"
#include "wsJson/ws_json.h"
#include "file.h"
#include "path.h"

#define MAX_MAP_NAME_COUNT 28

typedef struct Map {
    char name[MAX_MAP_NAME_COUNT];
    Color backgroundColor;
    Path* paths;
    int32_t pathsCount;
} Map;

typedef enum MapStateTabType {
    MAP_STATE_TAB_OVERALL,
    MAP_STATE_TAB_PATH,
    MAP_STATE_TAB_TEXTURES,

    MAP_STATE_TAB_NUM,
} MapStateTabType;

typedef enum MapStatePopUp {
    MAP_STATE_POP_UP_ADD_PATH = (1 << 0),
} MapStatePopUp;

typedef enum MapStateState {
    MAP_STATE_STATE_CREATE_PATH = (1 << 0),
} MapStateState;

typedef struct MapState {
    wsJson* json;
    Map map;
    const char* filepath;
    bool saved;
    MapStateTabType tabs[MAP_STATE_TAB_NUM];
    int32_t currentTab;
    uint32_t popUps;
    uint32_t states;
    PathPointType followingPointType;
    int32_t followingPoint;
    int32_t followingPointPath;
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
