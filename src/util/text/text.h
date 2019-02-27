#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <stdbool.h>

#include "util/surface.h"
#include "util/vector.h"

typedef struct s_text
{
	char			*string;
	t_vector2i		size;
	t_vector2i		position;
	SDL_Color		color;
	TTF_Font	*font;
	SDL_Texture	*texture;
} t_text;

t_text		*new_text(char *string, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, t_vector2i position);
int         change_text_string(t_text *text, SDL_Renderer *renderer, char *new);
void		render_text(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect);
void		free_text(t_text *text);
#endif