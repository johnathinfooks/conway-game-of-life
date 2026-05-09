#ifndef SHARED3D_H
#define SHARED3D_H

// defines

#include "../../lib/raylib.h"
#include <math.h>

// game

#define CELL_COLUMNS 24
#define CELL_ROWS 24
#define CELL_DEPTH 24

typedef enum {
    alive3D = 1,
    dead3D = 0
} State3D;

typedef struct {
    State3D state;
    int pos_x;
    int pos_y;
    int pos_z;
} Cell3D;

typedef struct {
Cell3D table[CELL_COLUMNS][CELL_ROWS][CELL_DEPTH];
Cell3D next[CELL_COLUMNS][CELL_ROWS][CELL_DEPTH];
} Environment3D;

Environment3D initEnv3D();
void step3D(Environment3D *Env3D);

// render

void render3D(Environment3D *Env3D);

#endif // SHARED3D_H
