#include <stdbool.h>

#define PERCENT_CHANCE_FOR_A_4 ( RAND_MAX / 50 )
#define nr_start_tiles 2

typedef enum direction {
  DIR_UP,
  DIR_RIGHT,
  DIR_DOWN,
  DIR_LEFT,
  DIR_UNKNOWN
} direction;

void game_init(void);

void game_add_random_tile(void);

bool game_is_finsihed(void);

void game_move(direction direction);

void game_draw(void);

bool game_won(void);

bool game_moved(void);
