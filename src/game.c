// #include <stdio.h>
#include "rl.h"
#include "shared.h"

Environment2D initEnv2D()
{
    Environment2D Env;
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            Env.table[i][j].pos_x = i;
            Env.table[i][j].pos_y = j;
            Env.table[i][j].state = dead;
        }
    }

    // NOTE: cool starting options:

    // ====================================================
    // two gliders dont crash
    // Env.table[4][5].state = alive;
    // Env.table[5][5].state = alive;
    // Env.table[6][5].state = alive;
    // Env.table[6][6].state = alive;
    // Env.table[5][7].state = alive;
    // Env.table[1 + 10][1 + 10].state = alive;
    // Env.table[1 + 10][2 + 10].state = alive;
    // Env.table[1 + 10][3 + 10].state = alive;
    // Env.table[2 + 10][1 + 10].state = alive;
    // Env.table[3 + 10][2 + 10].state = alive;

    // ====================================================
    // two gliders crashing and die
    // Env.table[4][5].state = alive;
    // Env.table[5][5].state = alive;
    // Env.table[6][5].state = alive;
    // Env.table[6][6].state = alive;
    // Env.table[5][7].state = alive;
    // Env.table[1][1].state = alive;
    // Env.table[1][2].state = alive;
    // Env.table[1][3].state = alive;
    // Env.table[2][1].state = alive;
    // Env.table[3][2].state = alive;
    // ====================================================
    // random chaos
    // Env.table[4][5].state = alive;
    // Env.table[5][5].state = alive;
    // Env.table[6][5].state = alive;
    // Env.table[6][6].state = alive;
    // Env.table[5][7].state = alive;
    // Env.table[1][2].state = alive;
    // Env.table[2][1].state = alive;
    // Env.table[3][1].state = alive;
    // Env.table[3][2].state = alive;
    // Env.table[3][3].state = alive;
    // ====================================================
    // R-pentomino - maximum chaos from minimum cells
    Env.table[20][21].state = alive;
    Env.table[20][22].state = alive;
    Env.table[21][20].state = alive;
    Env.table[21][21].state = alive;
    Env.table[22][21].state = alive;

    return Env;
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
                Env3D.table[i][j][k].state = dead;
            }
        }
    }
    return Env3D;
}

int countNeighbors2D(Environment2D Env, int pos_x, int pos_y)
{
    int count = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue; // do not count self

            int nx = pos_x + i; // checking pos of x
            int ny = pos_y + j; // checking pos of y

            if (nx < 0) {
                nx = CELL_COLUMNS - 1;
            }
            if (nx >= CELL_COLUMNS) {
                nx = 0;
            }
            if (ny < 0) {
                ny = CELL_COLUMNS - 1;
            }
            if (ny >= CELL_COLUMNS) {
                ny = 0;
            }

            if (Env.table[nx][ny].state == alive)
                count++;
        }
    }
    return count;
}

int countNeighbors3D(Environment3D Env3D, int pos_x, int pos_y, int pos_z)
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

                if (Env3D.table[nx][ny][nz].state == alive)
                    count++;
            }
        }
    }
    return count;
}

void step2D(Environment2D *Env)
{
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            int neighbors = countNeighbors2D(*Env, Env->table[i][j].pos_x, Env->table[i][j].pos_y);
            if (neighbors < 2 || neighbors > 3) {
                Env->next[i][j].state = dead;
            } else if (neighbors == 3) {
                Env->next[i][j].state = alive;
            } else {
                Env->next[i][j].state = Env->table[i][j].state;
            }
        }
    }

    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            Env->table[i][j].state = Env->next[i][j].state;
        }
    }
}

void step3D(Environment3D *Env3D)
{
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            for (int k = 0; k < CELL_DEPTH; k++) {

                int neighbors = countNeighbors3D(*Env3D, Env3D->table[i][j][k].pos_x, Env3D->table[i][j][k].pos_y, Env3D->table[i][j][k].pos_z);
                if (neighbors < 7 || neighbors > 10) {
                    Env3D->next[i][j][k].state = dead;
                } else if (neighbors >= 7 && neighbors <= 10) {
                    Env3D->next[i][j][k].state = alive;
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
}

