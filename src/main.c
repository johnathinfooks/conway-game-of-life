#include "shared.h"

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Life");
    BeginDrawing();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(1 * SCALE_CONSTANT, 1 * SCALE_CONSTANT, 1 * SCALE_CONSTANT, 1 * SCALE_CONSTANT, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
