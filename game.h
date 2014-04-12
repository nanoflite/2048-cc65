#include <stdbool.h>

#include "tile.h"

#define nr_start_tiles 2
#define GOAL 11 

#define PERCENT_CHANCE_FOR_A_4 ( RAND_MAX / 50 )

typedef enum direction {
  DIR_UP,
  DIR_RIGHT,
  DIR_DOWN,
  DIR_LEFT,
  DIR_UNKNOWN
} direction;

typedef void (*game_draw_cell_cb)(tile *tile);

void game_init(game_draw_cell_cb draw_cell);

void game_add_random_tile(void);

bool game_is_finsihed(void);

void game_move(direction direction);

bool game_won(void);

bool game_moved(void);

void game_draw(void);

unsigned int game_score(void);

unsigned int game_best_score(void);

void game_dump(void);
