#include "rl.h"
#include "shared.h"
#include <raylib.h>
#include <unistd.h>

int main() {

    // raylib rendering
    // init
    InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_NAME);
    ShowCursor();
    // ToggleBorderlessWindowed();
    // SetWindowSize(GetScreenWidth(), GetScreenHeight());
    ToggleFullscreen();
    SetTargetFPS(30);
    Environment2D Env = initEnv2D();
    int pause_flag = 0;

    // loop
    while (!WindowShouldClose()) {

        if (IsKeyPressed(32)) {
            pause_flag = !pause_flag;
        }

        // drawing
        BeginDrawing();

        render2D(&Env);

        if (!pause_flag) {
            step(&Env);
        }

        EndDrawing();
    }

    // de-init
    CloseWindow();
    return 0;
}
