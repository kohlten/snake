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
	t_text *text;

    start_time = SDL_GetTicks();
	game->font = load_font("../fonts/FreeMono.ttf", 20);
	if (!game->font)
		return -1;
    game->fps_text = new_text_font("0", game->window->SDLrenderer, game->font,
        (SDL_Color){255, 255, 255, 255}, (t_vector2i){0, 0});
    if (!game->fps_text)
        return -1;
    //game->tail_amount_text = new_text_font("0", game->window->SDLrenderer, game->font,
    //    (SDL_Color){255, 255, 255, 255}, (t_vector2i){game->window->width - 50, 0});
    if (!game->tail_amount_text)
        return -1;
    game->food = new_food(CELL_SIZE);
    if (!game->food)
        return -1;
    game->snake = new_snake(CELL_SIZE);
    if (!game->snake)
        return -1;
    game->paused = false;
    game->frames = 0;
    change_pos_food(game->food, game->snake, game->window);
    printf("%p\n", game->tail_amount_text);
    printf("INIT: Took %d MS to init!\n", SDL_GetTicks() - start_time);
    return 0;
}

static void update(t_game *game)
{
    int fps;
    char *num;

    limit_fps(60);
    fps = calculate_fps();
    /*if (fps != -1)
    {
        num = ft_itoa(fps);
        game->fps_text = change_text_string(game->fps_text, game->window->SDLrenderer, num);
        free(num);
    }*/
    /*num = ft_itoa(game->snake->tail_length);
    game->tail_amount_text = change_text_string(game->tail_amount_text, game->window->SDLrenderer, num);
    free(num);*/
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
    render_text(game->fps_text, game->window->SDLrenderer, NULL);
    //render_text(game->tail_amount_text, game->window->SDLrenderer, NULL);
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
                    case SDLK_r:
                        reset_snake(game->snake, false);
                        break;
                    case SDLK_p:
                        game->paused = !game->paused;
                        break;
                    case SDLK_ESCAPE:
                        done = true;
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
    free_text(game->fps_text);
    free(game);
}
