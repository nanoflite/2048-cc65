#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"
#include "array.h"

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned int value)
{
  tile->x = x;
  tile->y = y;
  tile->value = value;
}

unsigned int tile_get_value(tile *tile)
{
  return tile->value;
}

void tile_set_value(tile *tile, unsigned int value)
{
  tile->value = value;
}

void tile_set_moved(tile *tile, bool moved)
{
  tile->moved = moved;
}

void tile_set_added(tile *tile, bool added)
{
  tile->added = added;
}
