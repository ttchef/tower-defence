
#include <stdio.h>

#include <raylib.h>

#include "GameManager.h"

void update() {

}

void draw() {
    DrawRectangle(400, 300, 50, 50, WHITE);
}

int main() {

    InitWindow(800, 600, "Tower-Defence");
    SetTargetFPS(60);

    GameManager game;
    pushGameState(&game, (GameState){STATE_MENU, update, draw});

    while (!WindowShouldClose()) {
        GameState* currentState = &game.states.states[game.states.top];
        currentState->update();

        BeginDrawing();
            ClearBackground(BLACK);
            currentState->draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
