/*                                                                              
 * timer.c                                                       
 *                                                                              
 * This program is free software; you can redistribute it and/or modify it      
 * under the terms of the GNU General Public License as published by the        
 * Free Software Foundation; either version 2, or (at your option) any          
 * later version.                                                               
 *                                                                              
 * This program is distributed in the hope that it will be useful, but          
 * WITHOUT ANY WARRANTY; without even the implied warranty of                   
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU            
 * General Public License for more details.                                     
 */

#include "timer.h"

Timer timer[NUM_TIMERS];

void timer_init(int i, TimerHandler handler, int max_count)
{
	timer[i].handler = handler;
	timer[i].max_count = max_count;
	timer[i].count = max_count;
}

inline void timer_start(int i)
{
	timer[i].running = 1;
}

inline void timer_stop(int i)
{
	timer[i].running = 0;
}

inline void timer_reset(int i)
{
	timer[i].count = timer[i].max_count;
}

inline void process_timers(int microsecs)
{
	int i;
	for (i = 0; i < NUM_TIMERS; i++)
	{
		if (timer[i].running) {
			timer[i].count -= microsecs;
			if (timer[i].count <= 0)
				timer[i].handler();
		}
	}
}
