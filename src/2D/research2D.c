#include "shared2D.h"
#include <stdlib.h>
#include <time.h>

Environment2D R_initEnv2D() {
    Environment2D Env;
    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            Env.table[i][j].pos_x = i;
            Env.table[i][j].pos_y = j;
            Env.table[i][j].state = dead2D;
        }
    }

    srand(time(NULL));
    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            if (rand() % 10 < 3)
                Env.table[i][j].state = alive2D;

    return Env;
}

#include <stdlib.h>  // for rand()

int R_sign(int x) {
    return (x > 0) - (x < 0);
}

int R_countNeighbors(Environment2D Env, int pos_x, int pos_y)
{
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = pos_x + i;
            int ny = pos_y + j;
            if (nx < 0 || nx >= CELL_COLUMNS) continue;
            if (ny < 0 || ny >= CELL_ROWS) continue;
            if (Env.table[nx][ny].state == alive2D)
                count++;
        }
    }
    return count;
}

void R_step2D(Environment2D *Env)
{
    // Clear next buffer once at the start
    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            Env->next[i][j].state = dead2D;

    for (int i = 0; i < CELL_COLUMNS; i++) {
        for (int j = 0; j < CELL_ROWS; j++) {
            // Skip dead cells — they don't move
            if (Env->table[i][j].state != alive2D) continue;

            int n = R_countNeighbors(*Env, i, j);
            int di, dj;

            if (n >= 1) {
                // Has at least one neighbor — anchor in place
                di = i;
                dj = j;
            } else {
                // Completely isolated — compute gradient and try to migrate
                int gi = 0;
                int gj = 0;
                for (int q = -2; q <= 2; q++) {
                    for (int r = -2; r <= 2; r++) {
                        if (q == 0 && r == 0) continue;
                        int ni = i + q;
                        int nj = j + r;
                        if (ni < 0 || ni >= CELL_COLUMNS) continue;
                        if (nj < 0 || nj >= CELL_ROWS) continue;

                        if (Env->table[ni][nj].state == alive2D) {
                            int dist_sq = q*q + r*r;
                            gi += (q * 100) / dist_sq;
                            gj += (r * 100) / dist_sq;
                        }
                    }
                }

                // Move toward density
                di = i + R_sign(gi);
                dj = j + R_sign(gj);

                // Clamp to grid bounds
                if (di < 0) di = 0;
                if (di >= CELL_COLUMNS) di = CELL_COLUMNS - 1;
                if (dj < 0) dj = 0;
                if (dj >= CELL_ROWS) dj = CELL_ROWS - 1;

                // If target is already occupied in next buffer, stay put
                if (Env->next[di][dj].state == alive2D) {
                    di = i;
                    dj = j;
                }
            }

            // Place cell at chosen destination
            Env->next[di][dj].state = alive2D;
        }
    }

    // Copy next back to table
    for (int i = 0; i < CELL_COLUMNS; i++)
        for (int j = 0; j < CELL_ROWS; j++)
            Env->table[i][j].state = Env->next[i][j].state;
}
