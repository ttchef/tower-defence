
#include "Manager.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main() {

    Manager manager;
    managerInit(&manager);

    State fileState = {
        .type = PROGRAM_STATE_FILE, 
        .update = updateMapState, 
        .draw = drawMapState,
        .drawGui = drawMapStateGui,
    };

    pushState(&manager, fileState);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(manager.windowWidth, manager.windowHeight, "Editor");

    while (!WindowShouldClose()) {
        State* currentState = getCurrentState(&manager);
        currentState->update(&manager);

        BeginDrawing();

            ClearBackground(BLACK);
  
            BeginMode2D(manager.camera);
                currentState->draw(&manager);
            EndMode2D();
            
            currentState->drawGui(&manager);
            drawMenuBar(&manager);  
        EndDrawing();
    }

    CloseWindow();

    managerDeinit(&manager);

    return 0;
}

