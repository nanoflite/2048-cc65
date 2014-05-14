#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"
#include "array.h"

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned char value)
{
  tile->x = x;
  tile->y = y;
  tile->value = value;
}

unsigned char tile_get_value(tile *tile)
{
  return tile->value;
}

void tile_set_value(tile *tile, unsigned char value)
{
  tile->value = value;
}

void tile_set_moved(tile *tile, bool moved)
{
  if (moved) {
    tile->flags |= FLAG_MOVED;
  } else {
    tile->flags &= ~FLAG_MOVED;
  }
}

bool tile_moved(tile *tile)
{
  return FLAG_MOVED == ( tile->flags & FLAG_MOVED );
}

void tile_set_added(tile *tile, bool added)
{
  if (added) {
    tile->flags |= FLAG_ADDED;
  } else {
    tile->flags &= ~FLAG_ADDED;
  }
}
bool tile_added(tile *tile)
{
  return FLAG_ADDED == ( tile->flags & FLAG_ADDED );
}

void tile_set_dirty(tile *tile, bool dirty)
{
  if (dirty) {
    tile->flags |= FLAG_DIRTY;
  } else {
    tile->flags &= ~FLAG_DIRTY;
  }
}

bool tile_dirty(tile *tile)
{
  return FLAG_DIRTY == ( tile->flags & FLAG_DIRTY );
}

void tile_set_needs_drawing(tile *tile, bool needs_drawing)
{
  if (needs_drawing) {
    tile->flags |= FLAG_NEEDS_DRAWING;
  } else {
    tile->flags &= ~FLAG_NEEDS_DRAWING;
  }
}

bool tile_needs_drawing(tile *tile)
{
  return FLAG_NEEDS_DRAWING == ( tile->flags & FLAG_NEEDS_DRAWING );
}
