#include "util/text/text.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

SDL_Texture *load_from_rendered_text(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color)
{
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;

	if (!text || !font || !renderer)
		return NULL;
	text_surface = TTF_RenderText_Solid(font, text, color);
	if (!text_surface)
	{
		printf("Failed to render text to surface! SDL_tff Error: %s\n", TTF_GetError());
		return NULL;
	}
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (!text_texture)
	{
		printf("Failed to create texture! SDL Error: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_FreeSurface(text_surface);
	return text_texture;
}

TTF_Font *load_font(char *name, int size)
{
	TTF_Font *font;

	if (!name)
		return NULL;
	font = TTF_OpenFont(name, size);
	if (!font)
	{
		printf("WARNING: Failed to open font %s!\n", name);
		return NULL;
	}
	return font;
}

void free_text(t_text *text)
{
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	if (text->string)
		free(text->string);
	free(text);
	text = NULL;
}

t_text *new_text_font(char *string, SDL_Renderer *renderer, char *font_name, int size, SDL_Color color, t_vector2i position)
{
	t_text *text;

	if (!font_name || !renderer)
		return NULL;
	if (!string)
		printf("WARNING: Creating text with empty string!\n");
	text = ft_memalloc(sizeof(t_text));
	if (!text)
		return NULL;
	text->font = load_font(font_name, size);
	if (!text->font)
	{
		free_text(text);
		return NULL;
	}
	if (strcmp(string, "") != 0)
		text = change_text_string(text, renderer, string);
	else
	{
		printf("ERROR: Trying to create a text with an empty string!\n");
		free_text(text);
		return NULL;
	}
	text->color = color;
	text->position = position;
	return text;
}

t_text *new_text(char *string, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, t_vector2i position)
{
	t_text *text;

	if (!renderer || !font)
	{
		printf("ERROR: Renderer or font null!\n");
		return NULL;
	}
	if (!string)
		printf("WARNING: Creating text with empty string!\n");
	text = ft_memalloc(sizeof(t_text));
	if (!text)
		return NULL;
	text->font = font;
	if (!text->font)
	{
		free_text(text);
		return NULL;
	}
	if (strcmp(string, "") != 0)
		text = change_text_string(text, renderer, string);
	else
	{
		printf("ERROR: Trying to create a text with an empty string!\n");
		free_text(text);
		return NULL;
	}
	text->color = color;
	text->position = position;
	return text;
}
