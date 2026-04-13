#ifndef SHARED_H
#define SHARED_H

#include <raylib.h>
#include <stdio.h>
#include "rl.h"

typedef enum {
    alive = 1,
    dead = 0
} State;

typedef struct {
    State state;
    int pos_x;
    int pos_y;
} Cell;

typedef struct {
    Cell table[CELL_COLUMNS][CELL_ROWS];
    Cell next[CELL_COLUMNS][CELL_ROWS];
} Environment;

// FUNCTIONS

// game

Environment initEnv();
int count_neighbors(Environment Env, int pos_x, int pos_y);
void step(Environment *Env);
void printEnv(Environment Env);

#endif // SHARED_H
