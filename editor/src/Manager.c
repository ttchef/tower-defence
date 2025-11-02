
#include "Manager.h"
#include "definies.h"
#include "map.h"
#include "menuBar.h"

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

void managerInit(Manager* manager) {
    memset(manager, 0, sizeof(Manager));

    // Top Menu
    manager->bar.height = 40;

    // Gui
    manager->guiWidth = 300;
    manager->guiHeight = 780;

    // Map
    manager->mapWidth = 1280 - manager->guiWidth;
    manager->mapHeight = manager->guiHeight;

    // Window
    manager->windowWidth = manager->mapWidth + manager->guiWidth;
    manager->windowHeight = manager->mapHeight + manager->bar.height;

    // Camera
    manager->camera.offset = (Vector2){0, manager->bar.height};
    manager->camera.zoom = 1;

    initMneuBar(manager);
}

void managerDeinit(Manager *manager) {
    deinitMapState(manager);
}

