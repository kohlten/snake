#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <stdbool.h>

#include "libft.h"
#include "util/vector.h"
#include "util/window.h"

typedef enum
{
    SNAKE_STOP     = -1,
	SNAKE_UP       =  0,
	SNAKE_DOWN     =  1,
	SNAKE_LEFT     =  2,
	SNAKE_RIGHT    =  3
} Snake_Direction;

typedef struct s_snake
{
	t_vector2f		pos;
	long			tail_length;
    int             size;
	Snake_Direction	direction;
	SDL_Rect		snakeRect;
	t_list			*tail;
    bool            reset;
} t_snake;

t_snake *new_snake(int size);
void change_direction_snake(t_snake *snake, Snake_Direction direction);
void update_snake(t_snake *snake);
void delete_snake(t_snake *snake);
void increase_size_snake(t_snake *snake);
void move_tail_back(t_snake *snake);
void display_snake(t_snake *snake, t_window *window);
void reset_snake(t_snake *snake);
void contain_snake(t_snake *snake, t_window *window);
void hit_tail_snake(t_snake *snake);
#endif