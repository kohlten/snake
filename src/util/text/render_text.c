#include "util/text/text.h"
#include <stdio.h>

void render_text_font(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect)
{
	if (text->text_font.texture)
	{
		if (rect)
			SDL_RenderCopy(renderer, text->text_font.texture, NULL, rect);
		else
		{
			printf("%d %d %d %d\n", text->position.x, text->position.y, text->size.x, text->size.y);
			SDL_RenderCopy(renderer, text->text_font.texture, NULL,
				&(SDL_Rect){text->position.x, text->position.y, text->size.x, text->size.y});
		}
	}
}

void render_text_bitmap(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect)
{

}

void render_text(t_text *text, SDL_Renderer *renderer, SDL_Rect *rect)
{
	if (text->type == TYPE_FONT)
		render_text_font(text, renderer, rect);
	else if (text->type == TYPE_BITMAP)
		render_text_bitmap(text, renderer, rect);
	else
		printf("WARNING: Failed to display text due to malformed text struct!");
}