#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "tile.h"

/**
 * @brief Draws a tile on the screen.
 *
 * This function draws a cell on the screen, using the tile to get to the location and value.
 *
 * @param tile Pointer to the tile that needs drawing.
 */
void
screen_draw_cell(tile *tile);

/**
 * @brief Draws the winning message or screen.
 *
 * This function is called when the goal of 2048 is reached. Use it for drawing a winning
 * message.
 */
void
screen_draw_you_won(void);

/**
 * @brief Draws a game over message.
 *
 * This function  is called when the game is over, i.e. when no more moves are available.
 * It is not called when to goal is reached.
 */
void
screen_draw_game_over(void);

/**
 * @brief Draw the message 'restart y/n?' or similar and recobstruct screen afterwards.
 *
 * This function gets called when the user presses the 'Q' key and is used to ask for a game
 * restart. The function should return true when a restart is needed.
 * This function needs to reconstruct the screen area it destroyed.
 *
 * @return bool True when restart needed.
 */
bool
screen_draw_and_ask_restart(void);

/**
 * @brief First function called after game start. Use to show title screen.
 *
 * This function is called first and should be used to show the title screen.
 * You can do a keyboard press check here as well to proceed.
 * You can use this to do some platform specific setup stuff.
 * This function is called once during the lifetime of the game.
 */
void
screen_title(void);

/**
 * @brief Use to initialize the playing field.
 *
 * Use this function to setup the grid.
 * This function is called once during the lifetime of the game.
 */
void
screen_init(void);

/**
 * @brief Use to reinit the screen after wining or game over.
 */
void
screen_reinit(void);

/**
 * @brief Draw all the tiles.
 */
void
screen_draw(void);

/**
 * @brief Draw the score.
 *
 * This function draws the score.
 *
 * Use the the functions game_score() and game_best_score() to get the values.
 */
void
screen_draw_score(void);

#endif
