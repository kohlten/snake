#include "util/surface.h"

#include <string.h>
#include <stdio.h>

SDL_Surface *load_image_surface(const char *name, const SDL_PixelFormat *format)
{
	SDL_Surface *outputSurface;
	SDL_Surface *loadedSurface;

	loadedSurface = IMG_Load(name);
	if (!loadedSurface)
	{
		printf("Unable to load image %s SDL Error: %s\n", name, SDL_GetError());
		return NULL;
	}
	outputSurface = SDL_ConvertSurface(loadedSurface, format, 0);
	SDL_FreeSurface(loadedSurface);
	if (!outputSurface)
	{
		printf("Failed to optimize surface %s! SDL Error: %s\n", name, SDL_GetError());
		return NULL;
	}
	return outputSurface;
}

SDL_Texture *load_image_texture(const char *name, SDL_Renderer *renderer)
{
	SDL_Texture *output_texture;
	SDL_Surface *loaded_surface;

	loaded_surface = IMG_Load(name);
	if (!loaded_surface)
	{
		printf("Unable to load image %s SDL Error: %s\n", name, SDL_GetError());
		return NULL;
	}
	output_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	SDL_FreeSurface(loaded_surface);
	if (!output_texture)
	{
		printf("Failed to optimize surface %s! SDL Error: %s\n", name, SDL_GetError());
		return NULL;
	}
	return output_texture;
}

SDL_Surface *resize_surface(SDL_Surface *previous_surface, t_vector2i new_size, t_vector2i pos)
{
	SDL_Surface *new_surface;
	SDL_Rect output_rect;
	int out;

	new_surface = SDL_CreateRGBSurface(0, new_size.x, new_size.y, 32, 0, 0, 0, 0);
	if (!new_surface)
	{
		printf("Failed to create surface! SDL Error: %s\n", SDL_GetError());
		return NULL;
	}
	output_rect.x = pos.x;
	output_rect.y = pos.y;
	output_rect.w = new_size.x;
	output_rect.h = new_size.y;
	out = SDL_BlitScaled(previous_surface, NULL, new_surface, &output_rect);
	SDL_FreeSurface(previous_surface);
	if (out < 0)
	{
		printf("Failed to blit surface! SDL Error: %s\n", SDL_GetError());
		SDL_FreeSurface(new_surface);
		return NULL;
	}
	return new_surface;
}

void wipe_surface(SDL_Surface *surface, int color)
{
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, color, surface->h * surface ->pitch);
	SDL_UnlockSurface(surface);
}