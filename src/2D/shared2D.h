#ifndef SHARED2D_H
#define SHARED2D_H

// defines

#include "../../lib/raylib.h"
#include <math.h>

// game

#define CELL_COLUMNS 91
#define CELL_ROWS 51

typedef enum {
    alive2D = 1,
    dead2D = 0
} State2D;

typedef struct {
    State2D state;
    int pos_x;
    int pos_y;
} Cell2D;

typedef struct {
    Cell2D table[CELL_COLUMNS][CELL_ROWS];
    Cell2D next[CELL_COLUMNS][CELL_ROWS];
} Environment2D;

Environment2D initEnv2D();
void step2D(Environment2D *Env);

// rendering

#define SCALE_CONSTANT 28

void render2D(Environment2D *Env);

#endif // SHARED2D_H
