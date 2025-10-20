
#include "GameManager.h"
#include "definies.h"

int32_t pushGameState(GameManager *game, GameState state) {
    StateStack* stack = &game->states;
    if (stack->top + 1 >= MAX_GAME_STATES) return GAME_ERROR;
    stack->states[++stack->top] = state;
    return stack->top;
}

int32_t popGameState(GameManager *game) {
    StateStack* stack = &game->states;
    if (stack->top <= 0) return GAME_ERROR;
    int32_t pop = stack->top--;
    return pop;
}

GameState* getCurrentState(GameManager* game) {
    StateStack* stack = &game->states;
    return &stack->states[stack->top];
}

int32_t initGame(GameManager* game) {
    int32_t top = game->states.top;
    top++;
    return 0;
}
