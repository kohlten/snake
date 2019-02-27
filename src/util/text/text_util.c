//
// Created by kohlten on 2/27/19.
//

#include "text_util.h"

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
