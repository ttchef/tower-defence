
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "definies.h"
#include "playing/playing.h"

#define MAX_GAME_STATES 10

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
} GameStateType;

typedef struct {
    GameStateType type;
    void (*update)(GameManager*);
    void (*draw)(GameManager*);
} GameState;

typedef struct {
    GameState states[MAX_GAME_STATES];
    int32_t top;
} StateStack;

struct GameManager {
    StateStack states;
    Playing playing;   
};

// ==== State handling ==== 
int32_t pushGameState(GameManager* game, GameState state);
int32_t popGameState(GameManager* game);
GameState* getCurrentState(GameManager* game);

int32_t initGame(GameManager* game);

#endif
