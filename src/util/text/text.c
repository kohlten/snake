#include "util/text/text.h"

#include "util/text/text_util.h" // load_from_rendered_text

#include <string.h> // strcmp
#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <strings.h> // bzero

t_text *new_text(char *string, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, t_vector2i position)
{
	t_text *text;

	if (!renderer || !font)
	{
		printf("ERROR: Renderer or font null!\n");
		return NULL;
	}
	if (!string)
	{
		printf("EROROR: Creating text with empty string!\n");
		return NULL;
	}
	text = malloc(sizeof(t_text));
	if (!text)
		return NULL;
	bzero(text, sizeof(t_text));
	text->font = font;
	if (strcmp(string, "") != 0)
		change_text_string(text, renderer, string);
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

int change_text_string(t_text *text, SDL_Renderer *renderer, char *new)
{
	if (!text)
	{
		printf("ERROR: Cannot change the text of a null text!\n");
		return -1;
	}
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	text->texture = load_from_rendered_text(renderer, new, text->font, text->color);
	if (!text->texture)
		return -1;
	SDL_QueryTexture(text->texture, NULL, NULL, &text->size.x, &text->size.y);
	return 0;
}

void render_text(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect)
{
	if (text->texture) {
		if (rect)
			SDL_RenderCopy(renderer, text->texture, NULL, rect);
		else
			SDL_RenderCopy(renderer, text->texture, NULL,
						   &(SDL_Rect) {text->position.x, text->position.y, text->size.x, text->size.y});
	}
}

void free_text(t_text *text)
{
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	if (text->string)
		free(text->string);
	free(text);
}