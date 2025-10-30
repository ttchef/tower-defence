
#include "file.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "Manager.h"

int main() {

    Manager manager = {
        .windowWidth = 1280,
        .windowHeight = 780,
        .guiWidth = 300,
        .guiHeight = 780,
    };

    State fileState = {
        .type = PROGRAM_STATE_FILE, 
        .update = updateFileState, 
        .draw = drawFileState,
    };

    pushState(&manager, fileState);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(manager.windowWidth, manager.windowHeight, "Editor");

    while (!WindowShouldClose()) {
        State* currentState = getCurrentState(&manager);
        currentState->update(&manager);

        BeginDrawing();
            ClearBackground(BLACK);
            currentState->draw(&manager);;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

