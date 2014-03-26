#include <stdlib.h>

#include "tile.h"
#include "array.h"

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned int value)
{
  tile->x = x;
  tile->y = y;
  tile->value = value;
}

void tile_save_position(tile *tile)
{
  tile->previous_x = tile->x;
  tile->previous_y = tile->y;
}

void tile_set_pos(tile *tile, unsigned char x, unsigned char y)
{
  tile->x = x;
  tile->y = y;
}

unsigned int tile_get_value(tile *tile)
{
  return tile->value;
}

void tile_set_value(tile *tile, unsigned int value)
{
  tile->value = value;
}
