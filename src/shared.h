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
    int pos_z;
} Cell;

typedef struct {
    Cell table[CELL_COLUMNS][CELL_ROWS];
    Cell next[CELL_COLUMNS][CELL_ROWS];
} Environment2D;

typedef struct {
    Cell table[CELL_COLUMNS][CELL_ROWS][CELL_DEPTH];
    Cell next[CELL_COLUMNS][CELL_ROWS][CELL_DEPTH];
} Environment3D;



// FUNCTIONS

// game

Environment2D initEnv2D();
Environment3D initEnv3D();
int countNeighbors2D(Environment2D Env, int pos_x, int pos_y);
int countNeighbors3D(Environment3D Env3D, int pos_x, int pos_y, int pos_z);
void step2D(Environment2D *Env);
void printEnv2D(Environment2D Env);
void step3D(Environment3D *Env3D);
void render2D(Environment2D *Env);
void render3D(Environment3D *Env);

#endif // SHARED_H
