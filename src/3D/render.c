#include "shared3D.h"

Color assignColor(int neighborCount) {
    if (neighborCount <= 7)  return GRAY;
    if (neighborCount <= 10)  return BLUE;
    if (neighborCount <= 12) return (Color){126, 185, 120, 255};
    if (neighborCount <= 15) return YELLOW;
    if (neighborCount <= 16) return (Color){241, 145,  27, 255};
    return RED;
}

float assignOpacity(int neighborCount) {
    if (neighborCount <= 7)  return 0.1;
    if (neighborCount <= 10)  return 0.3;
    if (neighborCount <= 12) return 0.5;
    if (neighborCount <= 15) return 0.7;
    if (neighborCount <= 17) return 0.8;
    return 0.9;

}

void render3D(Environment3D *Env3D)
{
    Color backgroundColor = {38, 38, 38};
    ClearBackground(backgroundColor);

    DrawGrid(19, 2.0f);

    // print to window
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {
                if (Env3D->table[i][j][k].state == alive3D) {
                    DrawCube((Vector3){ i - 16, j, k - 16}, 1, 1, 1, Fade(assignColor(Env3D->table[i][j][k].neighborCount), assignOpacity(Env3D->table[i][j][k].neighborCount)));
                }
            }
        }
    }
}

