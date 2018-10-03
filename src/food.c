#include "food.h"
#include "libft.h"

#include <sodium.h>

t_food *new_food(int size)
{
    t_food *food;

    food = ft_memalloc(sizeof(t_food));
    if (!food)
    {
        printf("Failed to malloc food!\n");
        return NULL;
    }
    food->eaten = false;
    food->size = size;
    return food;
}

void change_pos_food(t_food *food, t_snake *snake, t_window *window)
{
    t_vector2f pos;
    t_vector2f *node_pos;
    t_list *tail;
    bool failed;
    int i = 0;
    int j;

    while (true)
    {
        failed = false;
        tail = snake->tail;
        pos.x = randombytes_uniform(window->width / food->size) * food->size;
        pos.y = randombytes_uniform(window->height / food->size) * food->size;
        printf("%f %f\n", pos.x, pos.y);
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
        printf("RUNNING %d %d\n", i, j);
        if (!failed)
            break;
        i++;
    }
    food->pos = pos;
}

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

void delete_food(t_food *food)
{
	free(food);
}