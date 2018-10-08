#include "util/text/text.h"
#include <string.h>
#include <stdio.h>

int init_font(void)
{
	if (!TTF_WasInit())
	{
		if (TTF_Init() == -1)
		{
			printf("ERROR: Failed to initialize TTF!\n");
			return -1;
		}
	}
	else
	{
		printf("WARNING: Trying to initialize font twice!\n");
		return -1;
	}
	return 0;
}

t_text *change_text_string(t_text *text, SDL_Renderer *renderer, char *new)
{
	if (!text)
	{
		printf("ERROR: Cannot change the text of a null text!\n");
		return NULL;
	}
	if (text->texture)
		SDL_DestroyTexture(text->texture);
	text->texture = load_from_rendered_text(renderer, new, text->font, text->color);
	if (!text->texture)
		printf("WANRING: Failed to set the new text!\n");
	SDL_QueryTexture(text->texture, NULL, NULL, &text->size.x, &text->size.y);
	return text;
}