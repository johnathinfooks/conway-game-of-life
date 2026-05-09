#include "shared2D.h"

Environment2D initEnv2D()
{
    Environment2D Env;
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            Env.table[i][j].pos_x = i;
            Env.table[i][j].pos_y = j;
            Env.table[i][j].state = dead2D;
        }
    }

    // NOTE: Optional: these are initial states
    // TODO: Make initial state an input to the function

    // R-pentomino - maximum chaos from minimum cells
    Env.table[20][21].state = alive2D;
    Env.table[20][22].state = alive2D;
    Env.table[21][20].state = alive2D;
    Env.table[21][21].state = alive2D;
    Env.table[22][21].state = alive2D;

    return Env;
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

            if (Env.table[nx][ny].state == alive2D)
                count++;
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
                Env->next[i][j].state = dead2D;
            } else if (neighbors == 3) {
                Env->next[i][j].state = alive2D;
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
