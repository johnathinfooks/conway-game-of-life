#ifndef SHARED_H
#define SHARED_H

#include <raylib.h>
#include "rl.h"

typedef enum {
    alive = 1,
    dead = 0
} State;

typedef struct {
    State state;
} Cell;

typedef struct {
    Cell table[CELL_COLUMNS][CELL_ROWS];
    Cell next[CELL_COLUMNS][CELL_ROWS];
} Env;

#endif // SHARED_H
