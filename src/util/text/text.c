#include "util/text/text.h"
#include <string.h>
#include <stdio.h>

int init_font(void)
{
	if (!TTF_WasInit())
	{
		if (!TTF_Init())
		{
			printf("ERROR: Failed to initialize TTF!\n"); 
		}
	}
	else
	{
		printf("WARNING: Trying to initialize font twice!\n");
		return -1;
	}
	return 0;
}

void change_text_string(t_text *text, char *new)
{
	if (text->dynamic)
		text->string = strdup(new);
	else
		printf("WARNING: Cannot change the string of a static text!\n");
}