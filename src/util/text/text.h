#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <stdbool.h>

#include "util/surface.h"
#include "util/vector.h"
//#include "util/text/glyph_table.h"


enum
{
	TYPE_FONT,
	TYPE_BITMAP,
};

typedef struct s_text_font
{
	TTF_Font	*font;
	SDL_Texture	*texture;
} t_text_font;

typedef struct s_text_bitmap
{
	SDL_Texture *image;
	//t_glyph_table *table;
} t_text_bitmap;

typedef struct s_text
{
	char			*string;
	t_text_font		text_font;
	t_text_bitmap	text_bitmap;
	int				type;
	t_vector2i		size;
	t_vector2i		position;
	SDL_Color		color;
} t_text;

int			init_font(void);

SDL_Texture	*load_from_rendered_text(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color);
TTF_Font	*load_font(char *name, int size);
t_text		*new_text_font(char *string, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, t_vector2i position);
t_text 		*change_text_string_font(t_text *text, SDL_Renderer *renderer, char *new);

void		render_text_bitmap(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect);
void 		render_text_font(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect);
void		render_text(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect);

void		free_text_font(t_text *text);
void		free_text(t_text *text);
#endif