
#include <stdio.h>

#include <raylib.h>

#include "GameManager.h"

int main() {

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

