
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "definies.h"

#define MAX_GAME_STATES 10

typedef enum {
    STATE_MENU,
    STATE_PLAYIHNG,
} GameStateType;

typedef struct {
    GameStateType type;
    void (*update)();
    void (*draw)();
} GameState;

typedef struct {
    GameState states[MAX_GAME_STATES];
    int32_t top;
} StateStack;

typedef struct {
    StateStack states;
} GameManager;

int32_t pushGameState(GameManager* game, GameState state);
int32_t popGameState(GameManager* game);
GameState* getCurrentState(GameManager* game);

#endif
