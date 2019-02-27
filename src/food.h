/**
 * @defgroup Food
 * @{
 */

#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h> // bool

#include "snake.h" // t_snake
#include "util/vector.h" // t_vector2f
#include "util/window.h" // t_window

/**
 * Food object
 */
typedef struct s_food
{
    /** The current top left corner of the food */
	t_vector2f pos;
	/** If the food has been eaten */
	bool       eaten;
	/** The size of the food in pixels */
    int        size;
} t_food;

t_food *new_food(int size);
void change_pos_food(t_food *food, t_snake *snake, t_window *window);
void display_food(t_food *food, t_window *window);
void delete_food(t_food *food);

#endif

/**
 * @}
 */