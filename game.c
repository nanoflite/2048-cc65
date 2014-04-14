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
static unsigned char get_random_value(void);
static bool moves_available(void);
static bool matching_tiles_available(void);

static unsigned int best_score = 0;

bool won;
bool moved;
game_draw_cell_cb draw_cell_cb;
unsigned int score;

void game_init(game_draw_cell_cb draw_cell)
{
  draw_cell_cb = draw_cell;

  _randomize();
  grid_init();
  insert_start_tiles();
  won = false;
  moved = true;
  score = 0;
}

void game_add_random_tile(void)
{
  tile *tile;
  unsigned char value;

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

static bool can_has_add(tile *t, tile *tn)
{
  unsigned char value;
  unsigned char next_value;

  if (tile_dirty(t)) {
    return false;
  }

  if (tile_dirty(tn)) {
    return false;
  }

  value = tile_get_value(t);
  if ( value == 0 ) {
    return false;
  }

  next_value = tile_get_value(tn);
  if ( value != next_value ) {
    return false;
  } 

  return true;
}

static void _pull_up(grid_get_f get_tile, signed char row_start, signed char row_vector)
{
  signed char column;
  signed char row;
  signed char next_row;
  unsigned char value;
  unsigned char next_value;
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

      if (can_has_add(tile, next_tile)) {
        value++;
        score += value;
        if (score > best_score) {
          best_score = score;
        }
        if ( GOAL == value ) {
          won = true;
        }
        tile_set_value( tile, value );
        tile_set_added( tile, true );
        tile_set_dirty( tile, true );
        tile_set_value( next_tile, 0 );
        tile_set_dirty( next_tile, false );
        moved = true;
      }

      if (value == 0 && next_value != 0) {
        tile_set_value(tile, next_value );
        tile_set_moved(tile, true);
        tile_set_value(next_tile, 0);
        tile_set_dirty(tile, tile_dirty(next_tile));
        tile_set_dirty(next_tile, false);
        moved = true;
      }

    }
    row += row_vector; 
  
  } 
}

static void _draw_cell(tile *tile)
{
  draw_cell_cb( tile ); 
  tile_set_moved( tile, false );
  tile_set_added( tile, false );
}

static void reset(void)
{
  char i;
  char j;
  tile *tile;

  for(i=0;i<width;i++){
    for(j=0;j<width;j++){
      tile = grid_get(i,j);
      tile_set_dirty(tile, false);
    }
  }

}

static void pull_up(grid_get_f get_tile, signed char row_start, signed char row_vector)
{
  char i;
  reset();
  for(i=0;i<width-1;i++) {
    _pull_up(get_tile, row_start, row_vector);
    grid_draw(_draw_cell);
  }
}

void game_draw(void)
{
  grid_draw(_draw_cell);
}

static void insert_start_tiles(void)
{
  unsigned char i;

  for(i=0;i<nr_start_tiles;i++) {
    game_add_random_tile();
  }
}

static unsigned char get_random_value(void)
{
  if (rand() < PERCENT_CHANCE_FOR_A_4) {
    return 2;
  }
  return 1;
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
  unsigned char value;

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

void game_dump(void)
{
  char i;
  char j;
  tile *tile;

  printf("\n");

  for(i=0;i<width;i++){
    for(j=0;j<width;j++){
      tile = grid_get(i, j);
      printf("i:%d, j:%d, x:%d, y:%d, v:%d\n", i, j, tile->x, tile->y, tile->value);
    }
  }

  while(!kbhit()) {}; cgetc();
  
}

unsigned int game_score(void)
{
  return score;
}

unsigned int game_best_score(void)
{
  return best_score;
}
