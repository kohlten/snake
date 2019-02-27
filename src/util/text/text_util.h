//
// Created by kohlten on 2/27/19.
//

#ifndef TEXT_UTIL_H
#define TEXT_UTIL_H

#include <SDL.h>
#include <SDL_ttf.h>

int			init_font(void);
SDL_Texture	*load_from_rendered_text(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color);
TTF_Font	*load_font(char *name, int size);

#endif
