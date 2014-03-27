#ifndef __TILE_H__
#define __TILE_H__

typedef struct tile {
  unsigned char x;
  unsigned char y;
  unsigned int value;
  bool moved;
  bool added;
} tile;

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned int value);

unsigned int tile_get_value(tile *tile);

void tile_set_value(tile *tile, unsigned int value);

void tile_set_moved(tile *tile, bool moved);

void tile_set_added(tile *tile, bool added);

#endif
