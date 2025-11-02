
#ifndef MANAGER_H
#define MANAGER_H

#include "definies.h"
#include "map.h"
#include "menuBar.h"

#define MAX_GAME_STATES 10

typedef enum StateType {
    PROGRAM_STATE_FILE,
    PROGRAM_STATE_MAP,
} StateType;

typedef struct State{
    StateType type;
    void (*update)(Manager*);
    void (*draw)(Manager*);
    void (*drawGui)(Manager*);
} State;

typedef struct StateStack {
    State states[MAX_GAME_STATES];
    int32_t top;
} StateStack;

struct Manager {
    int32_t windowWidth;
    int32_t windowHeight;
    int32_t mapWidth;
    int32_t mapHeight;
    int32_t guiWidth;
    int32_t guiHeight;

    Camera2D camera;
    StateStack stateHandler;
    MenuBar bar;
    MapState map;
};

// ==== State Handling ====
int32_t pushState(Manager* manager, State state);
int32_t popState(Manager* manager);
State* getCurrentState(Manager* manager);

void managerInit(Manager* manager);
void managerDeinit(Manager* manager);

#endif
