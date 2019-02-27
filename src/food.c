/**
 * @defgroup Food
 * @{
 */

#include "food.h" // Food struct

#include "util/list.h" // t_list

#include <stdlib.h> // malloc
#include <strings.h> // bzero

#include <sodium.h> // randombytes_uniform
#include <SDL.h> // SDL_Rect SDL_SetRenderDrawColor SDL_RenderFillRect

/**
 * Creates a new food object amd returns it
 * @param size Size to render the food
 * @return The new food object
 */
t_food *new_food(int size)
{
    t_food *food;

    food = malloc(sizeof(t_food));
    if (!food)
        return NULL;
    bzero(food, sizeof(t_food));
    food->eaten = false;
    food->size = size;
    return food;
}

/**
 * Chooses a random position. If it is not on the snake or the snake tail, place it.
 * Otherwise it will continue until it has found a spot to place the food.
 * @param food The food object
 * @param snake The snake object
 * @param window The window object
 */
void change_pos_food(t_food *food, t_snake *snake, t_window *window)
{
    t_vector2f pos;
    t_vector2f *node_pos;
    t_list *tail;
    bool failed;
    int i = 0;
    int j;

    do
    {
        failed = false;
        tail = snake->tail;
        pos.x = randombytes_uniform((uint32_t)window->width / food->size) * food->size;
        pos.y = randombytes_uniform((uint32_t)window->height / food->size) * food->size;
        j = 0;
        while (tail)
        {
            node_pos = tail->content;
            if (node_pos->x == pos.x && node_pos->y == pos.y)
            {
                failed = true;
                break;
            }
            tail = tail->next;
            j++;
        }
        i++;
    } while (failed);
    food->pos = pos;
}

/**
 * Displays the food on the SDL window
 * @param food The food object
 * @param window The window object
 */
void display_food(t_food *food, t_window *window)
{
    SDL_Rect rect;

    rect.x = food->pos.x;
    rect.y = food->pos.y;
    rect.w = food->size - 1;
    rect.h = food->size - 1;
    SDL_SetRenderDrawColor(window->SDLrenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(window->SDLrenderer, &rect);
}

/**
 * Frees the food from memory
 * @param food The food object
 */
void delete_food(t_food *food)
{
	free(food);
}

/**
 * @}
 */
