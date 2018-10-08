#include "util/text/text.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

/*SDL_Texture *loadFromRenderedText(SDL_Renderer *renderer, char *text, TTF_Font *font, SDL_Color color)
{
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;

	if (!text || !font || !renderer)
		return NULL;
	if (strcmp(text, "") == 0)
	{
		printf("loadFromRenderedText Error: Cannot create a font with no text!\n");
		return NULL;
	}
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
}*/

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
	if (text->font)
		TTF_CloseFont(text->font);
	if (text->string)
		free(text->string);
	free(text);
	text = NULL;
}

t_text *new_text_font(char *string, SDL_Renderer *renderer, char *font_name, int size)
{
	t_text *text;
	char *tmp;

	if (!font_name)
		return NULL;
	text = ft_memalloc(sizeof(t_text));
	if (!text)
		return NULL;
	tmp = font_name;
	while (tmp && *tmp!= '.')
		tmp++;
	if (strcmp(font_name, ".ttf") == 0)
	{
		text->dynamic = false;
		text->font = load_font(font_name, size);
		if (!text->font)
		{
			free_text(text);
			return NULL;
		}
	}
	else
	{
		if (!renderer)
		{
			printf("WARNING: Cannot create dynamic text without the SDL Renderer!\n");
			free_text(text);
			return NULL;
		}
		text->dynamic = true;
		text->font = NULL;
		text->texture = load_image_texture(font_name, renderer);
		if (!text->texture)
		{
			free_text(text);
			return NULL;
		}
	}
	text->string = strdup(string);
	return text;
}

/*t_text *new_text(char *text, SDL_Texture *font, TTF_Font *font)
{
	return NULL;
}*/
