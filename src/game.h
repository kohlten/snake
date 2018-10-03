#ifndef PLATFORMER_H
#define PLATFORMER_H

#include <stdbool.h>

#include "libft.h"
#include "util/fps.h"
#include "util/window.h"
#include "util/surface.h"

#include "food.h"
#include "snake.h"

#define CELL_SIZE 40

// CLEAN ME
typedef struct s_game
{
	t_window	*window;
	long		frames;
	TTF_Font	*font;
	SDL_Texture *fps_texture;
	SDL_Texture *tail_amount_texture;
	t_food *food;
	t_snake *snake;
	bool paused;
} t_game;

t_game *create_game();
int init_objects(t_game *game);
void run(t_game *game);
void clean_window(t_window *window);
void clean_game(t_game *game);

#endif