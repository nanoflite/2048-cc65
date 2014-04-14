#ifndef __TILE_H__
#define __TILE_H__

#include <stdbool.h>

#define FLAG_MOVED 1
#define FLAG_ADDED 2
#define FLAG_DIRTY 4

typedef struct tile {
  unsigned char x;
  unsigned char y;
  unsigned char value;
  unsigned char flags;
} tile;

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned char value);

unsigned char tile_get_value(tile *tile);

void tile_set_value(tile *tile, unsigned char value);

void tile_set_moved(tile *tile, bool moved);

bool tile_moved(tile *tile);

void tile_set_added(tile *tile, bool added);

bool tile_added(tile *tile);

void tile_set_dirty(tile *tile, bool dirty);

bool tile_dirty(tile *tile);

#endif
