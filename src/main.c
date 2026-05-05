#include "rl.h"
#include "shared.h"
#include <raylib.h>
#include <unistd.h>

int main() {

    // raylib rendering
    // init
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    SetTargetFPS(8);
    Environment Env = initEnv();

    // loop
    while (!WindowShouldClose()) {

        // drawing
        BeginDrawing();

        Color backgroundColor = {38, 38, 38};
        ClearBackground(backgroundColor);

        // print
        for (int i = 0; i < CELL_COLUMNS; i++) {
            for (int j = 0; j < CELL_ROWS; j++) {
                if (Env.table[i][j].state == alive) {
                    DrawRectangle(i * SCALE_CONSTANT, j * SCALE_CONSTANT, 1 * SCALE_CONSTANT, 1 * SCALE_CONSTANT, WHITE);
                } else {};
            }
        }

        step(&Env);

        EndDrawing();
    }

    // de-init
    CloseWindow();
    return 0;
}
