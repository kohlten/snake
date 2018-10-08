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
	t_vector2i  position;
	bool		dynamic;
	char		*string;
	SDL_Color	color;
} t_text;

int			init_font(void);

SDL_Texture	*load_from_rendered_text(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color);
TTF_Font	*load_font				(char *name, int size);
t_text		*new_text_font			(char *string, SDL_Renderer *renderer, char *font_name, int size, SDL_Color color, t_vector2i position);
t_text 		*new_text				(char *text, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, t_vector2i position);
t_text 		*change_text_string		(t_text *text, SDL_Renderer *renderer, char *new);

void 		render_text				(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect);

void		free_text				(t_text *text);
#endif