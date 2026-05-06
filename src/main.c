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









#include "raylib.h"
#include <math.h>

int pause_flag = 1;
int frame_count = 0;
const int TICK_RATE = 4; // Proportional to {FPS / N}

int main(void) {
    Environment3D Env3D = initEnv3D();
    InitWindow(GetScreenWidth(), GetScreenHeight(), WINDOW_NAME) ;
    ShowCursor();
    ToggleFullscreen();


    Camera3D camera = { 0 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float angle = 0.5f;
    float pitch = 0.4f;
    float distance = 24.0f;

    SetTargetFPS(FRAME_RATE);

    while (!WindowShouldClose()) {
        // Only rotate when left mouse button is held
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            angle += delta.x * 0.005f;
            pitch -= delta.y * 0.005f;

            if (pitch > 1.5f) pitch = 1.5f;
            if (pitch < -1.5f) pitch = -1.5f;
        }

        // Zoom with scroll wheel
        distance -= GetMouseWheelMove();
        if (distance < 4.0f) distance = 4.0f;

        // Spherical to cartesian
        camera.position = (Vector3){
            cosf(pitch) * sinf(angle) * distance,
            sinf(pitch) * distance,
            cosf(pitch) * cosf(angle) * distance
        };





        if (IsKeyPressed(32)) {
            pause_flag = !pause_flag;
        }




        BeginDrawing();
            BeginMode3D(camera);
                render3D(&Env3D);
            EndMode3D();
        EndDrawing();
    

if (!pause_flag && ++frame_count >= TICK_RATE) {
            step3D(&Env3D);
            frame_count = 0;
        }
        if (pause_flag) {
            if (IsKeyPressed(83)) { // s key
                step3D(&Env3D);
                render3D(&Env3D);
            }
        }








    }

    CloseWindow();
    return 0;
}
