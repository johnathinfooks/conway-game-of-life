#include "2D/shared2D.h"
#include "3D/shared3D.h"
#include <stdio.h>
#include <string.h>

void init2D() {

    // raylib init

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Conway's Game of Life 2D");
    ShowCursor();
    ToggleFullscreen();
    const int FRAME_RATE_2D = 60;
    SetTargetFPS(FRAME_RATE_2D);

    // game init

    Environment2D Env = initEnv2D();
    const int TICK_RATE_2D = 4; // priportional to {FPS / N}

    // runtime loop

    int pauseFlag = 1;
    int frameCount = 0;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(32)) {         // space key
            pauseFlag = !pauseFlag;
        }

        BeginDrawing();

        render2D(&Env);

        if (!pauseFlag && ++frameCount >= TICK_RATE_2D) {
            step2D(&Env);
            frameCount = 0;
        }
        if (pauseFlag) {
            if (IsKeyPressed(83)) {     // s key
                step2D(&Env);
                render2D(&Env);
            }
        }

        EndDrawing();
    }
}

void R_init2D() {

    // raylib init

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Conway's Game of Life 2D");
    ShowCursor();
    ToggleFullscreen();
    const int FRAME_RATE_2D = 60;
    SetTargetFPS(FRAME_RATE_2D);

    // game init

    Environment2D Env = R_initEnv2D();
    const int TICK_RATE_2D = 4; // priportional to {FPS / N}

    // runtime loop

    int pauseFlag = 1;
    int frameCount = 0;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(32)) {         // space key
            pauseFlag = !pauseFlag;
        }

        BeginDrawing();

        render2D(&Env);

        if (!pauseFlag && ++frameCount >= TICK_RATE_2D) {
            R_step2D(&Env);
            frameCount = 0;
        }
        if (pauseFlag) {
            if (IsKeyPressed(83)) {     // s key
                R_step2D(&Env);
                render2D(&Env);
            }
        }

        EndDrawing();
    }
}

void init3D() {

    // raylib init

    InitWindow(GetScreenWidth(), GetScreenHeight(), "Conway's Game of Life 2D");
    ShowCursor();
    ToggleFullscreen();
    const int FRAME_RATE_3D = 60;
    SetTargetFPS(FRAME_RATE_3D);

    Camera3D camera = { 0 };
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float angle = 0.5f;
    float pitch = 0.4f;
    float distance = 150.0f;

    // game init

    Environment3D Env = initEnv3D();
    const int TICK_RATE_3D = 4; // priportional to {FPS / N}

    // runtime loop

    int pauseFlag = 1;
    int frameCount = 0;

    while (!WindowShouldClose()) {

        // cam rotate around origin
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            angle += delta.x * 0.005f;
            pitch -= delta.y * 0.005f;

            if (pitch > 1.5f) pitch = 1.5f;
            if (pitch < -1.5f) pitch = -1.5f;
        }

        // cam zoom
        distance -= GetMouseWheelMove();
        if (distance < 4.0f) distance = 4.0f;

        // polar calc -> cartesian position
        camera.position = (Vector3){
            camera.target.x + cosf(pitch) * sinf(angle) * distance,
            camera.target.y + sinf(pitch) * distance,
            camera.target.z + cosf(pitch) * cosf(angle) * distance
        };

        if (IsKeyPressed(32)) {             // space key
            pauseFlag = !pauseFlag;
        }

        BeginDrawing();
        BeginMode3D(camera);
        render3D(&Env);
        EndMode3D();
        EndDrawing();

        if (!pauseFlag && ++frameCount >= TICK_RATE_3D) {
            step3D(&Env);
            frameCount = 0;
        }
        if (pauseFlag) {
            if (IsKeyPressed(83)) {         // s key
                step3D(&Env);
                render3D(&Env);
            }
        }
    }
}

char *helpString =  "\nconw {input option}"
                    "\nValid input options:"
                    "\n - help  : Prints this help message"
                    "\n - info  : Prints program information"
                    "\n - 2d    : initiates simulation in 2 dimensions of space"
                    "\n - 3d    : initiates simulation in 3 dimensions of space"
                    "\n - rsch  : initiates research simulation"
                    "\n\n";

char *infoString =  "\nConway's Game of Life"
                    "\nJohnathin Fooks"
                    "\nInformation goes here"
                    "\n\n";

// main

int main(int argc, char *argv[]) {

    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        printf("%s", helpString);
    }
    else if (argc == 2 && strcmp(argv[1], "info") == 0) {
        printf("%s", infoString);
    }
    else if (argc == 2 && strcmp(argv[1], "2d") == 0) {
        init2D();
    }
    else if (argc == 2 && strcmp(argv[1], "3d") == 0) {
        init3D();
    }
    else if (argc == 2 && strcmp(argv[1], "rsch") == 0) {
        R_init2D();
    }
    else {
        printf("\nInvalid Input. Use 'help' for help.\n\n");
    }

    return 0;
}
