#ifndef __TILE_H__
#define __TILE_H__

typedef struct tile {
  unsigned char x;
  unsigned char y;
  unsigned int value;
} tile;

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned int value);

unsigned int tile_get_value(tile *tile);

void tile_set_value(tile *tile, unsigned int value);

#endif
