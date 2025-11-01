
#include "file.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "Manager.h"

int main() {

    Manager manager;
    managerInit(&manager);

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
            drawMenuBar(&manager);    

            BeginMode2D(manager.camera);
                currentState->draw(&manager);;
            EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    managerDeinit(&manager);

    return 0;
}

