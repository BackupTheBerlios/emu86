/*                                                                              
 * emu86.h                                                                      
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

#ifndef __EMU86_H
#define __EMU86_H

#include "log.h"

#define PACKAGE "emu86"
#define VERSION "0.0.0"

int load_rom(char *filename, int offset, int size, char *md5);

void shutdown();

#endif /* __EMU86_H */
