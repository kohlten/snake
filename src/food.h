#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>
#include <SDL.h>

#include <snake.h>
#include "util/vector.h"
#include "util/window.h"

typedef struct s_food
{
	t_vector2f pos;
	bool       eaten;
    int        size;
} t_food;

t_food *new_food(int size);
void change_pos_food(t_food *food, t_snake *snake, t_window *window);
void display_food(t_food *food, t_window *window);
void delete_food(t_food *food);

#endif