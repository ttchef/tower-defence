
#include <stdio.h>

#include <raylib.h>

int main() {

    InitWindow(800, 600, "Tower-Defence");
    SetTargetFPS(60);

    int x = 80;
    int y = 100;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 1; i < 4; i++) {
                DrawRing((Vector2){400, 300}, (x++) / i, (y++) / i, 0, 360, i * 20, WHITE);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
