/*                                                                              
 * log.h                                                                     
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

#ifndef __LOG_H
#define __LOG_H

#define DEBUG

#ifndef LOG_CHAN
# define LOG_CHAN ""
#endif /* LOG_CHAN */

#define LOG_DEBUG 0
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERROR 3
#define LOG_FATAL 4

#define EMU_INFO(...)   log("(--)", LOG_CHAN, __VA_ARGS__)
#define EMU_WARN(...)   log("(!!)", LOG_CHAN, __VA_ARGS__)
#define EMU_ERROR(...)  log("(EE)", LOG_CHAN, __VA_ARGS__)
#define EMU_FATAL(...)  log("(FATAL)", LOG_CHAN, __VA_ARGS__), exit(0)

#ifdef DEBUG

# define EMU_DEBUG(...) log("(==)", LOG_CHAN, __VA_ARGS__)

#endif /* DEBUG */

int log_init(int enable, char *log_file);
void log(char *pfx, char *log_chan, char *fmt, ...);

#endif /* __LOG_H */
