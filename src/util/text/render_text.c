#include "util/text/text.h"
#include <stdio.h>

void render_text(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect)
{
	if (text->texture)
	{
		if (rect)
			SDL_RenderCopy(renderer, text->texture, NULL, rect);
		else
		{
			printf("%d %d %d %d\n", text->position.x, text->position.y, text->size.x, text->size.y);
			SDL_RenderCopy(renderer, text->texture, NULL,
				&(SDL_Rect){text->position.x, text->position.y, text->size.x, text->size.y});
		}
	}
}