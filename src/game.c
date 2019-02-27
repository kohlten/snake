/**
 * @defgroup Game
 * @{
 */

#include "game.h"

#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <strings.h> // bzero

/**
 * Creates a new game object and a new window.
 * @return The game object
 */
t_game *create_game()
{
    t_game *game;
    int width = 1080;
    int height = 720;
    int start_time;

    start_time = SDL_GetTicks();
    game = malloc(sizeof(t_game));
    if (!game)
        return NULL;
    bzero(game, sizeof(t_game));
    game->window = new_window(width, height);
    if (!game->window)
        return NULL;
    printf("WINDOW: Took %d MS to init window!\n", SDL_GetTicks() - start_time);
    return game;
}

/**
 * Initializes the values inside of the game object and creates the food and the snake.
 * @param game The game object
 * @return -1 if failed 0 if there are no errors
 */
int init_objects(t_game *game)
{
    int start_time;

    start_time = SDL_GetTicks();
    game->food = new_food(CELL_SIZE);
    if (!game->food)
        return -1;
    game->snake = new_snake(CELL_SIZE);
    if (!game->snake)
        return -1;
    game->paused = false;
    game->done = false;
    game->frames = 0;
    change_pos_food(game->food, game->snake, game->window);
    printf("INIT: Took %d MS to init!\n", SDL_GetTicks() - start_time);
    return 0;
}

/**
 * Updates the snake and the food if the game is not paused.
 * The snake will move every ten frames.
 * @param game The game object
 */
static void update(t_game *game)
{
    limit_fps(60);
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

/**
 * Displays the food and the snake to the widow
 * @param game The game object
 */
static void display(t_game *game)
{
    SDL_SetRenderDrawColor(game->window->SDLrenderer, 0, 0, 0, 255);
    SDL_RenderClear(game->window->SDLrenderer);
    display_food(game->food, game->window);
    display_snake(game->snake, game->window);
    SDL_RenderPresent(game->window->SDLrenderer);
    game->frames++;
}

/**
 * Gets events from the window.
 * If it's wasd, move the snake in the direction of the key pressed.
 * If r, it will reset the snake to the initial position.
 * If p, it will pause the game
 * If esc, it will exit the game
 * @param game
 */
static void events(t_game *game)
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            game->done = true;
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
                    game->done = true;
                    break;
                default:
                    break;
            }
        }
    }
}

/**
 * Runs the main game loop calling the events, update and display functions.
 * @param game The game object
 */
void run(t_game *game)
{
    while (!game->done)
    {
        events(game);
        update(game);
        display(game);
        game->frames++;
    }
}

/**
 * Frees all objects in the game object and frees the object.
 * @param game
 */
void clean_game(t_game *game)
{
    free_window(game->window);
    delete_food(game->food);
    delete_snake(game->snake);
    free(game);
}

/**
* @}
*/