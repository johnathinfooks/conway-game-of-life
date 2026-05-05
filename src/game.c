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

    // // optional: initial conditions
    Env.table[0][0].state = alive;
    Env.table[1][1].state = alive;
    Env.table[2][2].state = alive;
    Env.table[3][3].state = alive;
    Env.table[4][4].state = alive;
    Env.table[5][5].state = alive;

    // R-pentomino - maximum chaos from minimum cells
    Env.table[20][21].state = alive;
    Env.table[20][22].state = alive;
    Env.table[21][20].state = alive;
    Env.table[21][21].state = alive;
    Env.table[22][21].state = alive;

    return Env;
}

int count_neighbors(Environment2D Env, int pos_x, int pos_y)
{
    int count = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;

            int nx = pos_x + i;
            int ny = pos_y + j;

            if (nx < 0 || nx >= CELL_COLUMNS || ny < 0 || ny >= CELL_ROWS) // if on any edge, don't compute
                continue;

            if (Env.table[nx][ny].state == alive)
                count++;
        }
    }
    return count;
}

void step(Environment2D *Env)
{
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            int neighbors = count_neighbors(*Env, Env->table[i][j].pos_x, Env->table[i][j].pos_y);
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

// useless; raylibc
// void printEnv2D(Environment2D Env)
// {
//     printf("\033[H\033[J");
//     for (int i = 0; i < CELL_COLUMNS; i++) {
//         printf("\n");
//         for (int j = 0; j < CELL_ROWS; j++) {
//             printf("%d ", Env.table[i][j].state);
//         }
//     }
// }
