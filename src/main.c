#include "rl.h"
#include "shared.h"
#include <raylib.h>

// int main() {
//
//     // TODO: Make all this initializing stuff better and more organized
//
//     // raylib rendering
//     // init
//     InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_NAME);
//     ShowCursor();
//     // ToggleBorderlessWindowed();
//     // SetWindowSize(GetScreenWidth(), GetScreenHeight());
//     ToggleFullscreen();
//     SetTargetFPS(FRAME_RATE);
//     Environment2D Env = initEnv2D();
//     int pause_flag = 1;
//     int frame_count = 0;
//     const int TICK_RATE = 4; // Proportional to {FPS / N}
//
//     // loop
//     while (!WindowShouldClose()) {
//
//         if (IsKeyPressed(32)) {
//             pause_flag = !pause_flag;
//         }
//
//         BeginDrawing();
//
//         render2D(&Env);
//
//         if (!pause_flag && ++frame_count >= TICK_RATE) {
//             step(&Env);
//             frame_count = 0;
//         }
//         if (pause_flag) {
//             if (IsKeyPressed(83)) { // s key
//                 step(&Env);
//                 render2D(&Env);
//             }
//         }
//
//         EndDrawing();
//     }
//
//     // de-init
//     CloseWindow();
//     return 0;
// }


// #include <math.h>
//
// int main()
// {
//     InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_NAME);
//     Camera3D cam = { 0 };
//
//     float time = GetTime();
//     float rad = 10.0f;
//     cam.position.x = sinf(time) * rad;
//     cam.position.z = cosf(time) * rad;
//     cam.position.y = 5.0f; // Set camera height
//     cam.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Look at origin
//
//     while (!WindowShouldClose()) {
//         UpdateCamera(&cam, CAMERA_FREE); // Or skip this if doing manual orbital movement
//
//     }
//
//     CloseWindow();
// }
