#ifndef __GRID_H__
#define __GRID_H__

#include <stdbool.h>

#include "tile.h"
#include "array.h"

#define width (4)

void grid_init(void);

void grid_draw(void);

tile *grid_random_available_cell(void);

void grid_available_cells(array *cells);

bool grid_cells_are_available(void);

tile *grid_get(signed char x, signed char y);

bool grid_within_bounds(signed char x, signed char y);

#endif
