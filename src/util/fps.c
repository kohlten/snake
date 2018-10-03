#include "util/fps.h"

#include <stdio.h>

float calculate_fps()
{
	static unsigned int previous_time = 0;
	static int frames = 0;
	unsigned int current;
	int previous;

	// Get the current time in ticks
	current = SDL_GetTicks();

	// If the current minus the previous time is greater than 1 second
	// Set the previous time and return the frames
	if ((current - previous_time) >= 1000)
	{
		previous_time = current;
		previous = frames;
		frames = 0;
		return previous;
	}
	frames++;
	return -1;
}

void limit_fps(int fps)
{
	static unsigned int start_time = 0;
	int frameTicks;
	int ticks_per_frame;

	if (start_time == 0)
	{
		start_time = SDL_GetTicks();
		return;
	}
	// If we are limiting
	if (fps > 0)
	{
		// Calculate how many ticks we need to wait
		// For each frame(1000 MS = 1 SEC)
		ticks_per_frame = 1000 / fps;
		// Get how many ticks have passed in this frame
		frameTicks = start_time - SDL_GetTicks();
		// If we ran the frame faster than the time
		if (frameTicks < ticks_per_frame)
		{
			//printf("%d, %d\n", ticks_per_frame, frameTicks);
			// Delay the remaining time
			SDL_Delay(ticks_per_frame - frameTicks);
		}
		start_time = SDL_GetTicks();
	}
}


