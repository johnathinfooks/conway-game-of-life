#include "shared2D.h"

// TODO: Put somewhere else
const int PADDING_PX = 4;

void render2D(Environment2D *Env)
{
    Color backgroundColor = {38, 38, 38};
    ClearBackground(backgroundColor);

    DrawRectangleLines(1, 1, CELL_COLUMNS * SCALE_CONSTANT, CELL_ROWS * SCALE_CONSTANT, WHITE);

    // print to window
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            if (Env->table[i][j].state == alive2D) {
                DrawRectangle(i * SCALE_CONSTANT + PADDING_PX / 2, j * SCALE_CONSTANT + PADDING_PX / 2, SCALE_CONSTANT - PADDING_PX, SCALE_CONSTANT - PADDING_PX, WHITE);
            }
        }
    }
}


