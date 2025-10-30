
#include "Manager.h"

int32_t pushState(Manager *manager, State state) {
    StateStack* stack = &manager->stateHandler;
    if (stack->top + 1 >= MAX_GAME_STATES) return -1;
    stack->top++;
    stack->states[stack->top] = state;
    return stack->top;
}

int32_t popState(Manager *manager) {
    StateStack* stack = &manager->stateHandler;
    if (stack->top <= 0) return -1;
    int32_t pop = stack->top--;
    return pop;
}

State* getCurrentState(Manager* manager) {
    StateStack* stack = &manager->stateHandler;
    return &stack->states[stack->top];
}

