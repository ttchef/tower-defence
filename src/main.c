
#include <stdio.h>

#include <raylib.h>

#include "GameManager.h"
#include "playing/playing.h"

int main() {

    srand(time(NULL));
    InitWindow(800, 600, "Tower-Defence");
    SetTargetFPS(60);

    GameManager game;
    initGame(&game);

    pushGameState(&game, (GameState){STATE_PLAYING, updatePlaying, drawPlaying});

    while (!WindowShouldClose()) {
        GameState* currentState = getCurrentState(&game);
        currentState->update(&game);

        BeginDrawing();
            ClearBackground(BLACK);
            currentState->draw(&game);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

