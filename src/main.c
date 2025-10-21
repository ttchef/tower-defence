
#include "GameManager.h"

int main() {

    GameManager* gm = malloc(sizeof(GameManager));
    initGame(gm);

    gm->states.top = pushGameState(gm, (GameState){STATE_PLAYING, updatePlaying, drawPlaying});

    while (!WindowShouldClose()) {
        gm->deltaTime = GetFrameTime();
        GameState* currentState = getCurrentState(gm);
        handleInput(gm);
        currentState->update(gm);

        BeginDrawing();
            ClearBackground(BLACK);
            currentState->draw(gm);
        EndDrawing();
    }

    CloseWindow();
    free(gm);
    gm = NULL;

    return 0;
}

