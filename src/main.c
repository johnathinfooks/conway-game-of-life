#include "rl.h"
#include "shared.h"
#include <raylib.h>

int main() {

    // raylib rendering
    // init
    InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_NAME);
    ShowCursor();
    // ToggleBorderlessWindowed();
    // SetWindowSize(GetScreenWidth(), GetScreenHeight());
    ToggleFullscreen();
    SetTargetFPS(FRAME_RATE);
    Environment2D Env = initEnv2D();
    int pause_flag = 0;
    int frame_count = 0;
    const int TICK_RATE = 6; // Proportional to {FPS / N}

    // loop
    while (!WindowShouldClose()) {

        if (IsKeyPressed(32)) {
            pause_flag = !pause_flag;
        }

        BeginDrawing();

        render2D(&Env);

        if (!pause_flag && ++frame_count >= TICK_RATE) {
            step(&Env);
            frame_count = 0;
        }
        if (pause_flag) {
            if (IsKeyPressed(83)) {
                step(&Env);
                render2D(&Env);
            }
        }

        EndDrawing();
    }

    // de-init
    CloseWindow();
    return 0;
}
