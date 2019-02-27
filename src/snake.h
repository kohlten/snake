/**
 * @defgroup Snake
 * @{
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h> // SDL_Rect
#include <stdbool.h> // bool

#include "util/list.h" // t_list
#include "util/vector.h" // t_vector2f
#include "util/window.h" // t_window

/** Snake direction */
typedef enum
{
    SNAKE_STOP     = -1,
	SNAKE_UP       =  0,
	SNAKE_DOWN     =  1,
	SNAKE_LEFT     =  2,
	SNAKE_RIGHT    =  3
} Snake_Direction;

/** The snake object */
typedef struct s_snake
{
	/** Current position */
	t_vector2f		pos;
	/** How many tail nodes we have */
	long			tail_length;
	/** Size in pixels */
    int             size;
    /** Current direction */
	Snake_Direction	direction;
	/** The whole tail list */
	t_list			*tail;
	/** The end of the tail */
	t_list			*increase_tail;
} t_snake;

t_snake *new_snake(int size);
void change_direction_snake(t_snake *snake, Snake_Direction direction);
void update_snake(t_snake *snake);
void delete_snake(t_snake *snake);
void increase_size_snake(t_snake *snake);
void move_tail_back(t_snake *snake);
void display_snake(t_snake *snake, t_window *window);
void reset_snake(t_snake *snake, bool done);
void contain_snake(t_snake *snake, t_window *window);
void hit_tail_snake(t_snake *snake);
#endif

/**
 * @}
 */