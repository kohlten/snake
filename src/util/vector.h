#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vector2f
{
	double x;
	double y;
} t_vector2f;

typedef struct s_vector2i
{
	signed int x;
	signed int y;
} t_vector2i;

typedef struct s_vector2u
{
	unsigned int x;
	unsigned int y;
}	t_vector2u;

typedef struct s_vector2l
{
	signed long x;
	signed long y;
} t_vector2l;

typedef struct s_vector2ul
{
	unsigned long x;
	unsigned long y;
}	t_vector2lu;

#endif