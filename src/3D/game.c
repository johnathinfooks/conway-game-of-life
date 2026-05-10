#include "shared3D.h"
#include <stdlib.h>
#include <time.h>

int countNeighbors3D(Environment3D *Env3D, int pos_x, int pos_y, int pos_z)
{
    int count = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            for (int k = -1; k < 2; k++) {
                if (i == 0 && j == 0 && k == 0) continue; // do not count self

                int nx = pos_x + i; // checking pos of x
                int ny = pos_y + j; // checking pos of y
                int nz = pos_z + k; // checking pos of z

                // TODO: consider the topography
                // if (nx < 0) {
                //     nx = CELL_COLUMNS - 1;
                // }
                // if (nx >= CELL_COLUMNS) {
                //     nx = 0;
                // }
                // if (ny < 0) {
                //     ny = CELL_COLUMNS - 1;
                // }
                // if (ny >= CELL_COLUMNS) {
                //     ny = 0;
                // }

                if (Env3D->table[nx][ny][nz].state == alive3D)
                    count++;
            }
        }
    }
    return count;
}

Environment3D initEnv3D()
{
    Environment3D Env3D;
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {
                Env3D.table[i][j][k].pos_x = i;
                Env3D.table[i][j][k].pos_y = j;
                Env3D.table[i][j][k].pos_z = k;
                Env3D.table[i][j][k].state = dead3D;
            }
        }
    }

    // random initial conditions
    srand(time(NULL));
    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            for (int k = 0; k < CELL_DEPTH; k++)
                if (rand() % 10 < 1.1) Env3D.table[i][j][k].state = alive3D;

    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            for (int k = 0; k < CELL_DEPTH; k++)
                Env3D.table[i][j][k].neighborCount = countNeighbors3D(&Env3D, i, j, k);

    return Env3D;
}

void step3D(Environment3D *Env3D)
{
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {

                int neighbors = countNeighbors3D(Env3D, Env3D->table[i][j][k].pos_x, Env3D->table[i][j][k].pos_y, Env3D->table[i][j][k].pos_z);
                Env3D->next[i][j][k].neighborCount = neighbors;
                if (neighbors < 7 || neighbors > 10) {
                    Env3D->next[i][j][k].state = dead3D;
                } else if (neighbors >= 7 && neighbors <= 10) {
                    Env3D->next[i][j][k].state = alive3D;
                } else {
                    Env3D->next[i][j][k].state = Env3D->table[i][j][k].state;
                }
            }
        }
    }

    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {
                Env3D->table[i][j][k].state = Env3D->next[i][j][k].state;
            }
        }
    }

    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            for (int k = 0; k < CELL_DEPTH; k++)
                Env3D->table[i][j][k].neighborCount = countNeighbors3D(Env3D, i, j, k);
}

