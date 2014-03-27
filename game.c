#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <conio.h>

#include "game.h"
#include "grid.h"
#include "tile.h"


typedef tile* (*grid_get_f)(char x, char y);

char vector_x[] = {  0, 1, 0, -1 };
char vector_y[] = { -1, 0, 1,  0 };

static void insert_start_tiles(void);
static unsigned int get_random_value(void);
static bool moves_available(void);
static bool matching_tiles_available(void);

bool won;
bool moved;

void game_init(void)
{
  _randomize();
  grid_init();
  insert_start_tiles();
  won = false;
  moved = true;
}

void game_add_random_tile(void)
{
  tile *tile;
  unsigned int value;

  tile = grid_random_available_cell(); 
  if ( NULL == tile ) {
    return;
  }

  value = get_random_value();
  tile_set_value(tile, value);
}

bool game_moved(void)
{
  return moved;
}

bool game_won(void)
{
  return won;
}

bool game_is_finsihed(void)
{
  return ! moves_available() || won;
}

static void pull_up(grid_get_f get_tile, signed char row_start, signed char row_vector);
static void move_up(void);
static void move_down(void);
static void move_right(void);
static void move_left(void);

void game_move(direction direction)
{
  moved = false;
  switch (direction) {
    case DIR_UP:
      move_up();
      break;
    case DIR_DOWN:
      move_down();
      break;
    case DIR_RIGHT:
      move_right();
      break;
    case DIR_LEFT:
      move_left();
      break;
  }
}

static tile* get_xy(char x, char y)
{
  return grid_get(x, y);
}

static tile* get_yx(char x, char y)
{
  return grid_get(y, x);
}

static void move_up(void)
{
  pull_up(get_xy, 0, 1);
}

static void move_left(void)
{
  pull_up(get_yx, 0, 1);
}

static void move_down(void)
{
  pull_up(get_xy, width-1, -1);
}

static void move_right(void)
{
  pull_up(get_yx, width-1, -1);
}

static void _pull_up(grid_get_f get_tile, signed char row_start, signed char row_vector)
{
  char column;
  signed char row;
  signed char next_row;
  unsigned int value;
  unsigned int next_value;
  tile *next_tile;
  tile *tile;
  signed char i;

  row = row_start;
  for(i=0;i<width;i++) {
    for(column=0;column<width;column++) {
      tile = get_tile( column, row );
      value = tile_get_value(tile);
      
      next_row = row + row_vector;

      if ( ! grid_within_bounds( column, next_row ) ) {
        continue;
      }

      next_tile = get_tile( column, next_row );
      next_value = tile_get_value(next_tile);

      if (value != 0 && value == next_value) {
        tile_set_value(tile, value + next_value );
        tile_set_value(next_tile, 0);
        moved = true;
      }

      if (value == 0 && next_value != 0) {
        tile_set_value(tile, next_value );
        tile_set_value(next_tile, 0);
        moved = true;
      }

    }
    row += row_vector; 
  } 
}

static void pull_up(grid_get_f get_tile, signed char row_start, signed char row_vector)
{
  char i;
  for(i=0;i<width-1;i++) {
    _pull_up(get_tile, row_start, row_vector);
  }
}

void game_draw(void)
{
  grid_draw();
}

static void insert_start_tiles(void)
{
  unsigned char i;
  tile *tile;

  for(i=0;i<nr_start_tiles;i++) {
    tile = grid_random_available_cell();
    tile_set_value(tile, 2); 
  }
}

static unsigned int get_random_value(void)
{
  if (rand() < PERCENT_CHANCE_FOR_A_4) {
    return 4;
  }
  return 2;
}

static bool moves_available(void)
{
  return grid_cells_are_available() || matching_tiles_available();
}

static bool matching_tiles_available(void)
{
  unsigned char x;
  unsigned char y;
  unsigned char next_x;
  unsigned char next_y;
  direction direction;
  tile *next_tile;
  tile *tile;
  unsigned int value;

  for(y=0;y<width;y++) {
    for(x=0;x<width;x++) {
      tile = grid_get(x, y);
      value = tile_get_value(tile);
      if (0 != value) {
        for(direction=DIR_UP;direction<DIR_UNKNOWN;direction++) {
          next_x = x + vector_x[direction];
          next_y = y + vector_y[direction];
          next_tile = grid_get(next_x, next_y);
          if ( value == tile_get_value(next_tile) ) {
            return true;
          } 
        } 
      }
    }
  }

  return false;
}
