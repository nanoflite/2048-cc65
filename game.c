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
  /*
  char y[2];
  tile *tile;
  static char index = 0;

  y[0] = 1;
  y[1] = 3;

  tile = grid_get( 1, y[index] );
  tile_set_value(tile, 2);
  index++;
  index &= 3; 
  */
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

static void move(grid_get_f get_tile);
static void move_up(void);
// static void move_down(void);
// static void move_right(void);
static void move_left(void);

void game_move(direction direction)
{
  moved = false;
  switch (direction) {
    case DIR_UP:
      move_up();
      break;
    /*
    case DIR_DOWN:
      move_down();
      break;
    case DIR_RIGHT:
      move_right();
      break;
    */
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
  move(get_xy);
}

static void move_left(void)
{
  move(get_yx);
}

static void move(grid_get_f get_tile)
{
  unsigned char x;
  unsigned char y;
  tile *other_tile;
  tile *tile;
  unsigned char other_y;
  unsigned int value;
  unsigned int other_value;

  for(x=0;x<width;x++) {

    other_y = 0;

    for(y=0;y<width;y++) {

      tile = get_tile( x, y );
      value = tile_get_value(tile);

      if ( 0 != value &&  y != other_y ) {

        other_tile = get_tile( x, other_y );
        other_value = tile_get_value(other_tile);
        
        if (value == other_value) {
          tile_set_value(other_tile, value + other_value );
          tile_set_value(tile, 0);
          moved = true;
          other_y = y;
        } else {
          if ( y != other_y ) {
            if ( 0 != other_value ) {
              other_tile = get_tile( x, other_y + 1 );
              other_y++; 
            }
            tile_set_value(tile, 0);
            tile_set_value(other_tile, value);
            moved = true;
          }
        }
      }
    }
  }
}

void game_draw(void)
{
  grid_draw();
}

static void insert_start_tiles(void)
{
  tile *tile;

  // 0123
  // _2_2
  tile = grid_get(0, 1);
  tile_set_value(tile, 2); 

  tile = grid_get(0, 3);
  tile_set_value(tile, 2); 

  // 0123
  // 422_
  tile = grid_get(1, 0);
  tile_set_value(tile, 4); 

  tile = grid_get(1, 1);
  tile_set_value(tile, 2); 

  tile = grid_get(1, 2);
  tile_set_value(tile, 2); 

  /*
  unsigned char i;
  tile *tile;

  for(i=0;i<nr_start_tiles;i++) {
    tile = grid_random_available_cell();
    tile_set_value(tile, 2); 
  }
  */
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
