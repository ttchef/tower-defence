
#include "GameManager.h"
#include "definies.h"
#include "playing/playing.h"
#include <raylib.h>

int32_t pushGameState(GameManager *game, GameState state) {
    StateStack* stack = &game->states;
    if (stack->top + 1 >= MAX_GAME_STATES) return GAME_ERROR;
    stack->top++;
    stack->states[stack->top] = state;
    return stack->top;
}

int32_t popGameState(GameManager *game) {
    StateStack* stack = &game->states;
    if (stack->top <= 0) return GAME_ERROR;
    int32_t pop = (stack->top)--;
    return pop;
}

GameState* getCurrentState(GameManager* game) {
    StateStack* stack = &game->states;
    return &stack->states[stack->top];
}

int32_t initGame(GameManager* game) {

    srand(time(NULL));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Tower-Defence");
    SetTargetFPS(60);

    // TODO: fix overwrite error
    initPlaying(game);
    game->states.top = -1;
    return 0;
}

void handleInput(GameManager *gm) {
    handlePlayingInput(gm);
}

