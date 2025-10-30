
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <stdint.h>

#include "Manager.h"

void update(Manager* manager);
void draw(Manager* manager);
void drawGui(Manager* manager);

int main() {

    Manager manager = {
        .windowWidth = 1280,
        .windowHeight = 780,
        .guiWidth = 300,
        .guiHeight = 780,
    };

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(manager.windowWidth, manager.windowHeight, "Editor");

    while (!WindowShouldClose()) {
        update(&manager);

        BeginDrawing();
            ClearBackground(BLACK);
            draw(&manager);
            drawGui(&manager);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void update(Manager* manager) {
    int32_t a = manager->windowWidth;
    a++;
}

void draw(Manager* manager) {
    int32_t a = manager->windowWidth;
    a++;   
}

void drawGui(Manager* manager) {
    int32_t guiStart = manager->windowWidth - manager->guiWidth;

    DrawRectangle(guiStart, 0, manager->guiWidth, manager->guiHeight, DARKGRAY);
}

