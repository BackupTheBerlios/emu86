/*                                                                              
 * timer.h                                                               
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

#ifndef __TIMER_H
#define __TIMER_H

#define NUM_TIMERS 1

#define TIMER_FDC 0

typedef void (*TimerHandler)();

typedef struct _timer {
	int running;
	int count;
	int max_count;
	TimerHandler handler;
} Timer;

extern Timer timer[NUM_TIMERS];

void timer_init(int i, TimerHandler handler, int max_count);

inline void timer_start(int i);
inline void timer_stop(int i);
inline void timer_reset(int i);

inline void process_timers(int microsecs);

#endif /* __TIMER__H */
