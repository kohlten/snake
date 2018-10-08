#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <stdbool.h>

#include "util/surface.h"
#include "util/vector.h"


typedef struct s_text
{
	TTF_Font	*font;
	SDL_Texture	*texture;
	t_vector2i	size;
	bool		dynamic;
	char		*string;
} t_text;

int init_font(void);
#endif