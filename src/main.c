
#include "GameManager.h"
#include <math.h>
#include <raylib.h>

int main() {

    GameManager* gm = malloc(sizeof(GameManager));
    initGame(gm);

    gm->states.top = pushGameState(gm, (GameState){STATE_PLAYING, updatePlaying, drawPlaying});

    while (!WindowShouldClose()) {
        gm->deltaTime = GetFrameTime();
        GameState* currentState = getCurrentState(gm);
        gm->screenWidth = GetScreenWidth();
        gm->screenHeight = GetScreenHeight();
        handleInput(gm);
        currentState->update(gm, gm->deltaTime);

        BeginDrawing();
            ClearBackground(DARKGREEN);
            currentState->draw(gm);
        EndDrawing();
            
    }

    CloseWindow();
    free(gm);
    gm = NULL;

    return 0;
}

