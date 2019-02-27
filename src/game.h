/**
 * @defgroup Game
 * @{
 */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h> // bool

#include "util/fps.h" // t_fps
#include "util/window.h" // t_window
#include "util/text/text.h" // t_text
#include "food.h" // t_food
#include "snake.h" // t_snake

/** How large each cell is in pixels */
#define CELL_SIZE 40

/**
 * Game struct that holds every object and data of the game.
 */
typedef struct s_game
{
    /** Window struct */
	t_window	*window;
	/** How many frames have passed */
	long		frames;
	/** Food object */
	t_food 		*food;
	/** Snake object */
	t_snake 	*snake;
	/** If the game is paused or not */
	bool 		paused;
	/** If we are exited yet */
	bool		done;
} t_game;

t_game *create_game();
int init_objects(t_game *game);
void run(t_game *game);
void clean_game(t_game *game);

#endif

/**
 * @}
 */