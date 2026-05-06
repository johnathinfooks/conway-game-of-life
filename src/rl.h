#include <raylib.h>

#ifndef RL_H
#define RL_H

#define WINDOW_NAME "Conway's Game of Life"

#define FRAME_RATE 60

#define CELL_COLUMNS 48
#define CELL_ROWS 48
#define CELL_DEPTH 48
#define SCALE_CONSTANT 27

#define WINDOW_WIDTH (CELL_COLUMNS * SCALE_CONSTANT)
#define WINDOW_HEIGHT (CELL_ROWS * SCALE_CONSTANT)

#endif // RL_H
