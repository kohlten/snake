#include "game.h"
#include <stdio.h>

// Add config for game
t_game *create_game()
{
    t_game *game;
    int width = 1080;
    int height = 720;
    int start_time;

    start_time = SDL_GetTicks();
    game = malloc(sizeof(t_game));
    if (!game)
    {
        // Later replace with logger
        printf("Could not malloc the game!\n");
        return NULL;
    }
    game->window = new_window(width, height);
    if (!game->window)
        return NULL;
    printf("WINDOW: Took %d MS to init window!\n", SDL_GetTicks() - start_time);
    return game;
}

// Seperate this function out
int init_objects(t_game *game)
{
    int start_time;

    start_time = SDL_GetTicks();
    game->font = TTF_OpenFont("fonts/PlayfairDisplay-Black.ttf", 28);
    if (!game->font)
    {
        printf("Failed to load font!\n");
        return -1;
    }
    game->fps_texture = NULL;
    game->tail_amount_texture = NULL;
    game->food = new_food(CELL_SIZE);
    if (!game->food)
        return -1;
    game->snake = new_snake(CELL_SIZE);
    if (!game->snake)
        return -1;
    game->paused = false;
    game->frames = 0;
    change_pos_food(game->food, game->snake, game->window);
    printf("INIT: Took %d MS to init!\n", SDL_GetTicks() - start_time);
    return 0;
}

static void update(t_game *game)
{
    int fps;
    char *num;

    limit_fps(60);
    fps = calculate_fps();
    if (fps != -1)
    {
        num = ft_itoa(fps);
        if (game->fps_texture)
            SDL_DestroyTexture(game->fps_texture);
        game->fps_texture = loadFromRenderedText(game->window->SDLrenderer, num, game->font, (SDL_Color){255, 255, 255});
        free(num);
    }
    num = ft_itoa(game->snake->tail_length);
    if (game->tail_amount_texture)
            SDL_DestroyTexture(game->tail_amount_texture);
    game->tail_amount_texture = loadFromRenderedText(game->window->SDLrenderer, num, game->font, (SDL_Color){255, 255, 255});
    free(num);
    if (!game->paused)
    {
        if (game->snake->pos.x == game->food->pos.x && game->snake->pos.y == game->food->pos.y)
        {
            change_pos_food(game->food, game->snake, game->window);
            increase_size_snake(game->snake);
        }
        if (game->frames % 10 == 0)
        {
            update_snake(game->snake);
            move_tail_back(game->snake);
        }
        hit_tail_snake(game->snake);
        contain_snake(game->snake, game->window);
    }
}

static void display(t_game *game)
{
    SDL_SetRenderDrawColor(game->window->SDLrenderer, 0, 0, 0, 255);
    SDL_RenderClear(game->window->SDLrenderer);
    display_food(game->food, game->window);
    display_snake(game->snake, game->window);
    if (game->fps_texture)
        SDL_RenderCopy(game->window->SDLrenderer, game->fps_texture, NULL, 
        &(SDL_Rect){0, 0, 20, 25});
    if (game->tail_amount_texture)
        SDL_RenderCopy(game->window->SDLrenderer, game->tail_amount_texture, NULL, 
        &(SDL_Rect){game->window->width - 20, 0, 20, 25});
    SDL_RenderPresent(game->window->SDLrenderer);
    game->frames++;
}

// Take events into a seperate function
void run(t_game *game)
{
    SDL_Event e;
    bool done = false;

    while (!done)
    {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                done = true;
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_w:
                        change_direction_snake(game->snake, SNAKE_UP);
                        break;
                    case SDLK_s:
                        change_direction_snake(game->snake, SNAKE_DOWN);
                        break;
                    case SDLK_a:
                        change_direction_snake(game->snake, SNAKE_LEFT);
                        break;
                    case SDLK_d:
                        change_direction_snake(game->snake, SNAKE_RIGHT);
                        break;
                    case SDLK_i:
                        increase_size_snake(game->snake);
                        break;
                    case SDLK_r:
                        reset_snake(game->snake);
                        break;
                    case SDLK_p:
                        game->paused = !game->paused;
                        break;
                    default:
                        break;
                }
            }
        }
        update(game);
        display(game);
        game->frames++;
    }
}

void clean_game(t_game *game)
{
    free_window(game->window);
    delete_food(game->food);
    delete_snake(game->snake);
    free(game);
}
