#include "util/window.h"
#include <sodium.h>

t_window *new_window(int width, int height)
{
	t_window *window;
	SDL_DisplayMode dm;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Later replace with logger
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }
	window = malloc(sizeof(t_window));
    if (!window)
    {
        // Later replace with logger
        printf("Could not malloc the window!\n");
        return NULL;
    }
    window->SDLwindow = SDL_CreateWindow("Snake",
        (dm.w / 2) -  (width / 2), (dm.h / 2) - (height / 2), width, height, 0);
    if (!window->SDLwindow)
    {
        // Later replace with logger
        printf("SDL could not create a window! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }
    window->SDLrenderer = SDL_CreateRenderer(window->SDLwindow, -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_PRESENTVSYNC);
    if (!window->SDLrenderer)
    {
        printf("SDL could not create a renderer! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        // Later replace with logger
        printf("Could not initialize SDL_Image! SDL_image Error: %s\n", IMG_GetError());
        return NULL;
    }
    if (init_font() == -1)
    {
        printf("Could not initialize SDL_ttf! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }
    if (sodium_init() < 0)
    {
        printf("Could not initialize Sodium!\n"); 
        return NULL;
    }
    window->width = width;
    window->height = height;
    return window;
}

void free_window(t_window *window)
{

    // SDL2 *should* take care of these. Otherwise we get an invalid read. 
    //SDL_DestroyWindow(window->SDLwindow);
    //SDL_DestroyRenderer(window->SDLrenderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    free(window);
}