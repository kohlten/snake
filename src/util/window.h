#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include "util/text/text.h"

typedef struct s_window
{
	int width;
	int height;
	SDL_Window *SDLwindow;
	SDL_Renderer *SDLrenderer;
} t_window;

t_window *new_window(int width, int height);
void free_window(t_window *window);

#endif