
#ifndef MANAGER_H
#define MANAGER_H

#include "definies.h"
#include "file.h"

#define MAX_GAME_STATES 10

typedef enum StateType {
    PROGRAM_STATE_FILE,
    PROGRAM_STATE_MAP,
} StateType;

typedef struct State{
    StateType type;
    void (*update)(Manager*);
    void (*draw)(Manager*);
} State;

typedef struct StateStack {
    State states[MAX_GAME_STATES];
    int32_t top;
} StateStack;

struct Manager {
    int32_t windowWidth;
    int32_t windowHeight;
    int32_t guiWidth;
    int32_t guiHeight;

    StateStack stateHandler;
    FileState file;
};

// ==== State Handling ====
int32_t pushState(Manager* manager, State state);
int32_t popState(Manager* manager);
State* getCurrentState(Manager* manager);

#endif
