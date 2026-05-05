#include "shared.h"

void render2D(Environment2D *Env)
{
    Color backgroundColor = {38, 38, 38};
    ClearBackground(backgroundColor);

        // print
        for (int i = 0; i < CELL_COLUMNS; i++) {
            for (int j = 0; j < CELL_ROWS; j++) {
                if (Env->table[i][j].state == alive) {
                    DrawRectangle(i * SCALE_CONSTANT, j * SCALE_CONSTANT, 1 * SCALE_CONSTANT, 1 * SCALE_CONSTANT, WHITE);
                } else {};
            }
        }
}
