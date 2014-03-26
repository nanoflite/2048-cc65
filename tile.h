#ifndef __TILE_H__
#define __TILE_H__

typedef struct tile {
  unsigned char x;
  unsigned char y;
  unsigned int value;
  unsigned char previous_x;
  unsigned char previous_y;
} tile;

void tile_init(tile *tile, unsigned char x, unsigned char y, unsigned int value);

void tile_save_position(tile *tile);

void tile_set_pos(tile *tile, unsigned char x, unsigned char y);

unsigned int tile_get_value(tile *tile);

void tile_set_value(tile *tile, unsigned int value);

#endif
