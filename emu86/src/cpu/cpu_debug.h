/*                                                                              
 * cpu_debug.h
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

#ifndef __CPU_DEBUG_H
#define __CPU_DEBUG_H

void DEBUG(char *fmt, ...);

void cpu_dump();
void cpu_short_dump();
void cpu_dump_mem(int s, int b, int ial);

#endif /* __CPU_DEBUG_H */
