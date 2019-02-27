/**
 * @defgroup Snake
 * @{
 */

#include "snake.h"

#include <stdlib.h> // malloc
#include <strings.h> // bzero

/**
 * Creates and a new snake object and initializes its values.
 * @param size Size of the snake in pixels
 * @return NULL if failed or the snake object
 */
t_snake *new_snake(int size)
{
	t_snake *snake;

	snake = malloc(sizeof(t_snake));
	if (!snake)
		return NULL;
	bzero(snake, sizeof(t_snake));
	snake->direction = SNAKE_STOP;
	snake->size = size;
    snake->tail = lstnew(&snake->pos, sizeof(t_vector2f));
    snake->move_tail = NULL;
    snake->increase_tail = NULL;
	return snake;
}

/**
 * Changes the directed based off of the values in Snake_Direction
 * @param snake The snake object
 * @param direction The direction you want to change to
 */
void change_direction_snake(t_snake *snake, Snake_Direction direction)
{
	snake->direction = direction;
}

/**
 * Updates the snake. Move in the direction we are currently going.
 * @param snake The snake object
 */
void update_snake(t_snake *snake)
{
	switch (snake->direction)
	{
		case SNAKE_UP:
			snake->pos.y -= snake->size;
			break;
		case SNAKE_DOWN:
			snake->pos.y += snake->size;
			break;
		case SNAKE_LEFT:
			snake->pos.x -= snake->size;
			break;
		case SNAKE_RIGHT:
			snake->pos.x += snake->size;
			break;
        default:
            break;
	}
}

/**
 * Increases the size of the snake by allocating a new list object at the end of the snake.
 * @param snake The snake object
 */
void increase_size_snake(t_snake *snake)
{
    if (snake->increase_tail == NULL)
        snake->increase_tail = snake->tail;
    snake->tail_length++;
	snake->increase_tail->next = lstnew(&(t_vector2f){-snake->size, -snake->size}, sizeof(t_vector2f));
	snake->increase_tail = snake->increase_tail->next;
}

/**
 * Moves the snake tail positions one forward
 * @param snake The snake object
 */
void move_tail_back(t_snake *snake)
{
    if (!snake->move_tail)
        snake->move_tail = snake->tail;
    memcpy(snake->move_tail->content, &snake->pos, sizeof(t_vector2f));
    snake->move_tail = snake->move_tail->next;
}

/**
 * Displays the snake head and all of the tail nodes.
 * @param snake The snake object
 * @param window The window object
 */
void display_snake(t_snake *snake, t_window *window)
{
	SDL_Rect rect;
	t_list *tail;
	t_vector2f *pos;
    int i = 0;

    rect.w = snake->size - 1;
    rect.h = snake->size - 1;
    tail = snake->tail;
    SDL_SetRenderDrawColor(window->SDLrenderer, 0, 150, 0, 255);
    while (tail)
    {
    	if (tail->content)
    	{
	    	pos = tail->content;
	    	rect.x = pos->x;
	    	rect.y = pos->y;
	    	SDL_RenderFillRect(window->SDLrenderer, &rect);
	    }
    	tail = tail->next;
        i++;
    }
    SDL_SetRenderDrawColor(window->SDLrenderer, 0, 255, 0, 255);
    rect.x = snake->pos.x;
    rect.y = snake->pos.y;
    SDL_RenderFillRect(window->SDLrenderer, &rect);
}

/**
 * Frees the snake tail by going through each of the tail nodes and freeing their list.
 * @param tail The list of tail objects.
 */
static void free_tail_snake(t_list *tail)
{
    t_list *next;
    int i;

    i = 0;
    next = tail->next;
    while (tail)
    {
        lstfree(tail);
        tail = next;
        if (tail)
            next = tail->next;
        i++;
    }
}

/**
 * Resets the snake to the initial position and sets the tail length to 0.
 * @param snake The snake object
 * @param done Whether to allocate a new tail or not
 */
void reset_snake(t_snake *snake, bool done)
{
    snake->move_tail = NULL;
    snake->increase_tail = NULL;
    bzero(&snake->pos, sizeof(t_vector2f));
    change_direction_snake(snake, SNAKE_STOP);
    if (snake->tail_length == 0)
        return;
    free_tail_snake(snake->tail);
    if (!done)
        snake->tail = lstnew(&(t_vector2f){-snake->size, -snake->size}, sizeof(t_vector2f));
    else
        snake->tail = NULL;
    snake->tail_length = 0;
}

/**
 * Prevents the snake from leaving the play area.
 * @param snake The snake object
 * @param window The window object
 */
void contain_snake(t_snake *snake, t_window *window)
{
    if (snake->pos.x >= window->width  ||
        snake->pos.x < 0              ||
        snake->pos.y >= window->height ||
        snake->pos.y < 0)
        reset_snake(snake, false);
}

/**
 * Checks if the snake hit its own tail. If it has, reset the snake.
 * @param snake The snake object
 */
void hit_tail_snake(t_snake *snake)
{
    t_list *tail;
    t_vector2f *pos;
    int i = 0;
    int nodes = 0;

    if (!snake->tail)
        return;
    tail = snake->tail;
    while (tail)
    {
        pos = tail->content;
        if (pos->x == snake->pos.x && pos->y == snake->pos.y)
            nodes++;
        if (nodes > 1)
        {
            reset_snake(snake, false);
            break;
        }
        tail = tail->next;
        i++;
    }
}

/**
 * Frees the snake
 * @param snake The snake object
 */
void delete_snake(t_snake *snake)
{
    reset_snake(snake, true);
	free_tail_snake(snake->tail);
    free(snake);
}

/**
 * @}
 */
