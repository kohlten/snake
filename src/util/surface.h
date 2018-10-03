#ifndef SURFACE_H
#define SURFACE_H

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "vector.h"

SDL_Texture *load_image_texture(const char *name, SDL_Renderer *renderer);
SDL_Surface *load_image_surface(const char *name, const SDL_PixelFormat *format);
SDL_Surface *resize_surface(SDL_Surface *previous_surface, t_vector2i new_size, t_vector2i pos);
void wipe_surface(SDL_Surface *surface, int color);
SDL_Texture *loadFromRenderedText(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color);

#endif