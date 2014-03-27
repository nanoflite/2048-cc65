#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "grid.h"


tile grid[width][width];
tile tile_null;

void grid_init(void)
{
  unsigned char i;
  unsigned char j;

  for(i=0; i<width; i++) {
    for(j=0; j<width; j++) {
      tile *tile = &grid[i][j];
      tile_init(tile, j, i, 0);
    }
  }

  tile_init(&tile_null, 0, 0, 0);

}

void grid_draw(void)
{
  unsigned char i;
  unsigned char j;
  unsigned char x;
  unsigned char y;
  unsigned int value;
  tile *tile;

  y = 0; 
  for(i=0; i<width; i++) {
    x = 0;
    for(j=0; j<width; j++) {
      tile = &grid[i][j];
      value = tile_get_value(tile);
      if (0 != value) {
        gotoxy( x, y );
        cprintf("%d", value);  
      }
      x += 4;
    }
    y += 4;
  }
 
}

tile *grid_random_available_cell(void)
{
  tile *tile = NULL;
  array tiles;
  size_t length;
  size_t random_index;

  grid_available_cells(&tiles);
  
  length = array_length(&tiles);
  if ( length > 0 ) {
    random_index = rand() % length; 
    tile = array_get(&tiles, random_index);
  }

  array_destroy(&tiles);
  
  return tile;
}

void grid_available_cells(array *cells)
{
  unsigned char i;
  unsigned char j;
  tile *tile;
  unsigned int value;

  array_init(cells, width*width);
  for(i=0;i<width;i++) {
    for(j=0;j<width;j++) {
       tile = &grid[i][j];
        value = tile_get_value(tile);
        if (0 == value) {
          array_add(cells, tile);
        }
    }
  }
}

bool grid_cells_are_available(void)
{
  bool available;
  array cells;
  grid_available_cells(&cells);
  available = cells.length > 0;
  array_destroy(&cells);
  return available; 
}

tile* grid_get(signed char x, signed char y)
{
  if ( grid_within_bounds(x, y) ) {
    return &grid[y][x];
  }
  return NULL;
}

bool grid_within_bounds(signed char x, signed char y) {
  return x >= 0 && x < width && y >= 0 && y < width;
} 
