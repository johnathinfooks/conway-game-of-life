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
} Environment2D;

// FUNCTIONS

// game

Environment2D initEnv2D();
int count_neighbors(Environment2D Env, int pos_x, int pos_y);
void step(Environment2D *Env);
void printEnv2D(Environment2D Env);
void render2D(Environment2D *Env);

#endif // SHARED_H
