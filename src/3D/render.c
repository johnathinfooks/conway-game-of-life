#include "shared3D.h"

void render3D(Environment3D *Env3D)
{
    Color backgroundColor = {38, 38, 38};
    ClearBackground(backgroundColor);

    DrawGrid(18, 2.0f);

    // print to window
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {
                if (Env3D->table[i][j][k].state == alive3D) {
                    DrawCube((Vector3){ i - 19, j, k - 19}, 1, 1, 1, WHITE);
                }
            }
        }
    }
}
